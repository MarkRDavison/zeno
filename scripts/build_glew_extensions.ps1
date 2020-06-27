function Get-VisualStudioInstallPath {
	$pfPath = (dir env:'ProgramFiles(x86)').Value

	Write-Host "Program Files Path" $pfPath

	$vsPath = &(Join-Path $pfPath "\Microsoft Visual Studio\Installer\vswhere.exe") -property installationpath

	Write-Host "Visual Studio Path" $vsPath

	return $vsPath;
}

Write-Host "===================================" -ForegroundColor Yellow
Write-Host "Building Glew Extensions" -ForegroundColor Yellow
Write-Host "===================================" -ForegroundColor Yellow

Push-Directory

$visualStudioPath = Get-VisualStudioInstallPath

Write-Host "VS Path" $visualStudioPath

cd glew/build/vc15

$cmd = 'devenv glew.sln /upgrade'
Write-Host $cmd -ForegroundColor Cyan
#Invoke-Expression $cmd

$cmd = 'devenv glew.sln /build ' + $BuildType + ' /projectconfig ' + $BuildType
Write-Host $cmd -ForegroundColor Cyan
#Invoke-Expression $cmd

Pop-Directory