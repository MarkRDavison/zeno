Push-Location

Set-Location ..

mkdir external

Set-Location external

wget https://kcat.strangesoft.net/openal-binaries/openal-soft-1.20.1-bin.zip -O OpenAL.zip

7z x OpenAL.zip -oOpenAL

Get-ChildItem

Set-Location OpenAL

Get-ChildItem

Set-Location ..

Get-ChildItem

Pop-Location