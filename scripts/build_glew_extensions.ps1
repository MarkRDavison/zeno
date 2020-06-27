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

Push-Location

$visualStudioPath = Get-VisualStudioInstallPath

Write-Host "VS Path" $visualStudioPath
$BuildType = "Release"

$externLoc = Join-Path -Path $PSScriptRoot -ChildPath "../extern/"
Write-Host "ExternalLoc:" $externLoc
Set-Location $externLoc
Set-Location glew/build/vc15

$cmd = 'devenv glew.sln /upgrade'
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

$cmd = 'devenv glew_static.vcxproj /build ' + $BuildType + ' /projectconfig ' + $BuildType
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

$cmd = 'devenv glew_shared.vcxproj /build ' + $BuildType + ' /projectconfig ' + $BuildType
Write-Host $cmd -ForegroundColor Cyan
Invoke-Expression $cmd

Pop-Location