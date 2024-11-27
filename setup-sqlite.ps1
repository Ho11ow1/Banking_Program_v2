$sqliteVersion = "3470100"
$amalgamationUrl = "https://www.sqlite.org/2024/sqlite-amalgamation-$sqliteVersion.zip"
$dllUrl = "https://www.sqlite.org/2024/sqlite-dll-win-x64-$sqliteVersion.zip"
$outputPath = "ConsoleApplication2\sqlite"
$dllOutputPath = "ConsoleApplication2"
$amalgamationZip = "sqlite-amalgamation.zip"
$dllZip = "sqlite-dll.zip"

# Create the sqlite directory if it doesn't exist
New-Item -ItemType Directory -Force -Path $outputPath
New-Item -ItemType Directory -Force -Path $dllOutputPath

# Download both zip files
Write-Host "Downloading files..."
Invoke-WebRequest -Uri $amalgamationUrl -OutFile $amalgamationZip
Invoke-WebRequest -Uri $dllUrl -OutFile $dllZip

# Extract the contents
Expand-Archive -Path $amalgamationZip -DestinationPath "temp_amalgamation" -Force
Expand-Archive -Path $dllZip -DestinationPath "temp_dll" -Force

# Copy only the header files from amalgamation
Copy-Item "temp_amalgamation\sqlite-amalgamation-$sqliteVersion\*.h" -Destination $outputPath

# Find and copy the DLL file (searching recursively)
$dllFile = Get-ChildItem -Path "temp_dll" -Filter "sqlite3.dll" -Recurse | Select-Object -First 1
if ($dllFile) 
{
    Copy-Item $dllFile.FullName -Destination $dllOutputPath
    Write-Host "sqlite3.dll copied to $dllOutputPath"
}

# Find and copy the DEF file (searching recursively)
$defFile = Get-ChildItem -Path "temp_dll" -Filter "sqlite3.def" -Recurse | Select-Object -First 1
if ($defFile) 
{
    Copy-Item $defFile.FullName -Destination $outputPath
    Write-Host "sqlite3.def copied to $outputPath"
}

# Clean up
Remove-Item -Recurse -Force "temp_amalgamation"
Remove-Item -Recurse -Force "temp_dll"
Remove-Item $amalgamationZip
Remove-Item $dllZip

# Create .lib file using lib.exe - with improved error handling and debugging
Write-Host "Attempting to create .lib file..."

# Try to find Visual Studio installation
$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vsWhere) 
{
    $vsPath = & $vsWhere -latest -property installationPath
    if ($vsPath) 
    {
        Write-Host "Found Visual Studio at: $vsPath"
        
        # Create a temporary batch file to run the commands
        $tempBatch = "temp_lib_creation.bat" # @ must be at the beginning of the line for correct .ps1 syntax
@"
@echo off
call "$vsPath\Common7\Tools\VsDevCmd.bat"
cd /d "$outputPath"
lib /DEF:sqlite3.def /OUT:sqlite3.lib /MACHINE:X64
"@ | Out-File -FilePath $tempBatch -Encoding ASCII
        
        # Execute the batch file and capture output
        Write-Host "Executing lib command..."
        $result = cmd.exe /c $tempBatch 2>&1
        Write-Host $result
        
        # Clean up
        Remove-Item $tempBatch -ErrorAction SilentlyContinue
    } 
    else 
    {
        Write-Host "Failed to get Visual Studio installation path"
    }
} 
else 
{
    Write-Host "Could not find Visual Studio installation using vswhere.exe"
}

Write-Host "`nFinal Status:"
Write-Host "=============="
Write-Host "Header files location: $outputPath"

if (Test-Path "$dllOutputPath\sqlite3.dll") 
{
    Write-Host "sqlite3.dll: FOUND at $dllOutputPath"
} 
else 
{
    Write-Host "sqlite3.dll: MISSING"
}

if (Test-Path "$outputPath\sqlite3.lib") 
{
    Write-Host "sqlite3.lib: FOUND at $outputPath"
} 
else 
{
    Write-Host "sqlite3.lib: MISSING"
}