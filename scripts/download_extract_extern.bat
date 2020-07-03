pushd

cd ..

mkdir external

cd external

wget https://kcat.strangesoft.net/openal-binaries/openal-soft-1.20.1-bin.zip -O OpenAL.zip

7z x OpenAL.zip -oOpenAL

ls

cd OpenAL

ls

cd ..

ls

popd

# -DOPENALSOFT_ROOT="../../external/OpenAL"