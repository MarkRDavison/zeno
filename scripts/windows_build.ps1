function Generate-ZenoBuildFiles {
	param(
		[string] $BuildType,
		[string] $AdditionalConfigureParams
	)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Generating Build Files" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake -A Win32 -DGLEW_STATIC=ON -DCMAKE_BUILD_TYPE=' + $BuildType + ' ' + $AdditionalConfigureParams + ' ..'
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
	param(
		[string] $BuildType,		
		[Parameter(Mandatory=$true)]
		[string] $InstallRoot
	)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Installing Artifacts" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake --install . --prefix ' + $InstallRoot + ' --config ' + $BuildType
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
		[string] $InstallRoot,
		[string] $AdditionalConfigureParams
	)

	Generate-ZenoBuildFiles -BuildType $BuildType -AdditionalConfigureParams $AdditionalConfigureParams
	Build-ZenoSolution -BuildType $BuildType
	if ($InstallRoot){
		Install-ZenoArtifacts -BuildType $BuildType -InstallRoot $InstallRoot
	}
	Run-ZenoTests -BuildType $BuildType
}