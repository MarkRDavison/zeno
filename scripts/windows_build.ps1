function Purge-Zeno {
	Get-ChildItem -Recurse | Remove-Item -force -recurse
}

function Install-Glew {
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

	devenv /upgrade glew.sln

	$cmd = 'msbuild glew.sln /property:Configuration=' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd



	popd
}

function Generate-ZenoBuildFiles {
	param( [string] $BuildType)
	
	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Generating Build Files" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake -DGLEW_STATIC=True -DCMAKE_BUILD_TYPE=' + $BuildType + ' ..'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}
function Build-ZenoSolution{
	param( [string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Building Solution" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake --build . --config ' + $BuildType
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}
function Install-ZenoArtifacts{
	param( [string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Installing Artifacts" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	New-Item -Path $intall_dir_root -ItemType directory | Out-Null
	$cmd = 'cmake --install . --prefix installed --config ' + $build_type
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}
function Run-ZenoTests{
	param( [string] $BuildType)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Running Tests" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'ctest --build-config ' + $BuildType + ' --output-on-failure --no-label-summary --no-subproject-summary --progress'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}


$build_type = "Debug"
$intall_dir_root = "installed"

Purge-Zeno

Install-Glew -BuildType $build_type
Generate-ZenoBuildFiles -BuildType $build_type
Build-ZenoSolution -BuildType $build_type
#Install-ZenoArtifacts -BuildType $build_type
Run-ZenoTests -BuildType $build_type