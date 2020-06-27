function Get-VisualStudioInstallPath {
	$pfPath = (dir env:'ProgramFiles(x86)').Value

	Write-Host "Program Files Path" $pfPath

	$vsPath = &(Join-Path $pfPath "\Microsoft Visual Studio\Installer\vswhere.exe") -property installationpath

	Write-Host "Visual Studio Path" $vsPath

	return $vsPath;
}

function Build-GlewPowershell {
	param([string] $BuildType)

	$platform = 'x64'

	$pfPath = (dir env:'ProgramFiles(x86)').Value

	Write-Host $pfPath

	$vsPath = &(Join-Path $pfPath "\Microsoft Visual Studio\Installer\vswhere.exe") -property installationpath

	Write-Host $vsPath

	$dsPath = (Join-Path $vsPath "Common7\Tools\Microsoft.VisualStudio.DevShell.dll")

	Write-Host $dsPath

	pushd

	Import-Module $dsPath
	Enter-VsDevShell -VsInstallPath $vsPath -SkipAutomaticLocation

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Initializing pre-build" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	popd
	pushd

	cd ../extern/glew/build/vc15	
	
	$cmd = 'devenv /upgrade glew.sln'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

	$cmd = 'msbuild glew.sln /property:Configuration=' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

	popd
}

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
	param([string] $BuildType)
	Build-Glew -BuildType $BuildType
	Generate-ZenoBuildFiles -BuildType $BuildType
	Build-ZenoSolution -BuildType $BuildType
	Install-ZenoArtifacts -BuildType $BuildType
	Run-ZenoTests -BuildType $BuildType
}