function Generate-ZenoBuildFiles {
	param([string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Generating Build Files" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake -DGLEW_STATIC=ON -DCMAKE_BUILD_TYPE=' + $BuildType + ' ..'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

}
function Build-ZenoSolution {
	param([string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Building Solution" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake --build . --config ' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}
function Install-ZenoArtifacts {
	param([string] $BuildType)

	$install_dir_root = "installed"

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Installing Artifacts" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	New-Item -Path $install_dir_root -ItemType directory | Out-Null
	$cmd = 'cmake --install . --prefix ' + $install_dir_root + ' --config ' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}
function Run-ZenoTests {
	param([string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Running Tests" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'ctest --build-config ' + $BuildType + ' --output-on-failure --no-label-summary --no-subproject-summary --progress'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}

function Do-TheThing {
	param(
		[string] $BuildType,
		[bool] $Install
	)
	# Build-Glew -BuildType $BuildType
	Generate-ZenoBuildFiles -BuildType $BuildType
	Build-ZenoSolution -BuildType $BuildType
	if ($Install){
		Install-ZenoArtifacts -BuildType $BuildType
	}
	Run-ZenoTests -BuildType $BuildType
}