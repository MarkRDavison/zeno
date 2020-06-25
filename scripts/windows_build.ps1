$build_type = "Debug"
$intall_dir_root = "installed"

Remove-Item -Path $intall_dir_root -Recurse -ErrorAction SilentlyContinue

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Generating Build Files" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

$cmd = 'cmake -DCMAKE_BUILD_TYPE=' + $build_type + ' ..'
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Building Solution" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

$cmd = 'cmake --build . --config ' + $build_type
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Installing Artifacts" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

New-Item -Path $intall_dir_root -ItemType directory | Out-Null
$cmd = 'cmake --install . --prefix installed --config ' + $build_type
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Running Tests" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

$cmd = 'ctest --build-config ' + $build_type + ' --output-on-failure --no-label-summary --no-subproject-summary --progress'
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd