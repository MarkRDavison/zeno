
$intall_dir_root = "installed"

Remove-Item -Path $intall_dir_root -Recurse -ErrorAction SilentlyContinue

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Generating Build Files" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

cmake -G "Visual Studio 16 2019" --config Debug ..

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Building Solution" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

cmake --build . --config Debug

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Installing Artifacts" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

New-Item -Path $intall_dir_root -ItemType directory | Out-Null
cmake --install . --prefix installed --config Debug

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Running Tests" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

ctest --build-config Debug --output-on-failure --no-label-summary --no-subproject-summary --progress