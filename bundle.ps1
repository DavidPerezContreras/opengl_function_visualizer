# bundle.ps1
$ErrorActionPreference = "Stop"

Write-Host "Building and bundling OpenGL project..."

# Paths
$sourceDir = Get-Location
$buildDir = "$sourceDir\build"
$releaseDir = "$buildDir\Release"  # Corrected path
$vcpkgBinDir = "$buildDir\vcpkg_installed\x64-windows\bin"
$shadersDir = "$sourceDir\shaders"
$distDir = "$sourceDir\dist"

# Executable name
$exeName = "hello_world.exe"  # Match your actual target name
$exePath = Join-Path $releaseDir $exeName

# Step 1: Build the project in Release mode
Write-Host "Running CMake build in Release mode..."
cmake --build $buildDir --config Release

# Step 2: Create dist folder
if (Test-Path $distDir) {
    Remove-Item $distDir -Recurse -Force
}
New-Item -ItemType Directory -Path $distDir | Out-Null

# Step 3: Copy executable
if (!(Test-Path $exePath)) {
    Write-Warning "Executable not found at $exePath. Trying fallback path..."

    $altReleaseDir = "$buildDir\x64\Release"
    $exePath = Join-Path $altReleaseDir $exeName

    if (!(Test-Path $exePath)) {
        Write-Error "Executable not found in either expected location. Build may have failed."
        exit 1
    } else {
        $releaseDir = $altReleaseDir
    }
}
Copy-Item $exePath -Destination $distDir
Write-Host "Copied executable"

# Step 4: Copy required DLLs
$requiredDlls = @("glfw3.dll") # Add more if needed
foreach ($dll in $requiredDlls) {
    $dllPath = Join-Path $vcpkgBinDir $dll
    if (Test-Path $dllPath) {
        Copy-Item $dllPath -Destination $distDir
        Write-Host "Copied $dll"
    } else {
        Write-Warning "DLL not found: $dll"
    }
}

# Step 5: Copy shaders folder
if (Test-Path $shadersDir) {
    Copy-Item $shadersDir -Destination $distDir -Recurse
    Write-Host "Shaders copied"
} else {
    Write-Warning "Shaders folder not found"
}

Write-Host "Bundle complete. Find your distributable in: $distDir"
