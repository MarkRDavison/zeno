function Build-Glew {
	param([string] $BuildType)

	Write-Host "Building glew..."

	pushd

	$batPath = Join-Path -Path ${Env:ProgramFiles(x86)} -ChildPath 'Microsoft Visual Studio/Installer/vswhere.exe'

	$installationPath = . $batPath -property installationPath

	if ($installationPath -and (test-path "$installationPath\Common7\Tools\vsdevcmd.bat")) {
		& "${env:COMSPEC}" /s /c "`"$installationPath\Common7\Tools\vsdevcmd.bat`" -no_logo && set" | foreach-object {
			$name, $value = $_ -split '=', 2
			set-content env:\"$name" $value
		}
	}

	cd ../extern/glew/build/vc15

	$cmd = 'devenv glew.sln /upgrade'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

	$cmd = 'devenv glew.sln /build ' + $BuildType + ' /projectconfig ' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

	popd

}

function Generate-ZenoBuildFiles {
	param([string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Generating Build Files" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake -DCMAKE_BUILD_TYPE=' + $BuildType + ' ..'
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
	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Installing Artifacts" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	New-Item -Path $intall_dir_root -ItemType directory | Out-Null
	$cmd = 'cmake --install . --prefix installed --config ' + $BuildType
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


$build_type = "Release"
$intall_dir_root = "installed"

Build-Glew -BuildType $build_type
Generate-ZenoBuildFiles -BuildType $build_type
Build-ZenoSolution -BuildType $build_type
Install-ZenoArtifacts -BuildType $build_type
Run-ZenoTests -BuildType $build_type