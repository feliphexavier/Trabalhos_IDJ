# Trabalhos_IDJ

Como realizei o trabalho usando SDL3, SDL3_image e SDL3_mixer como dependências não incluídas no repositório.
Deixarei abaixo o processo que realizo para rodar no linux.

## Intalação e atualização de algumas ferramentas de build

```bash
sudo apt update
sudo apt install build-essential cmake git ninja-build
```
## Algumas das dependências necessárias para compilar o SDL3

```bash
sudo apt install pkg-config libasound2-dev libpulse-dev \
    libaudio-dev libfribidi-dev libjack-dev libsndio-dev \
    libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
    libxfixes-dev libxi-dev libxss-dev libxtst-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev \
    libgles2-mesa-dev libegl1-mesa-dev libdbus-1-dev \
    libibus-1.0-dev libudev-dev libthai-dev \
    libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev
```

## Dependências usadas para manipulação de audio e imagem (SDL3_image e SDL3_mixer)

```bash
sudo apt install libpng-dev libjpeg-dev libwebp-dev libtiff-dev \
    libflac-dev libvorbis-dev libopus-dev libopusfile-dev \
    libmpg123-dev libxmp-dev libwavpack-dev
```

# Para Rodar o projeto
Rodando a primeira vez costuma demorar bastante.
```bash
git clone https://github.com/feliphexavier/Trabalhos_IDJ.git
cd Trabalhos_IDJ
```
```bash
git clone --recursive https://github.com/libsdl-org/SDL.git
git clone --recursive https://github.com/libsdl-org/SDL_image.git
git clone --recursive https://github.com/libsdl-org/SDL_mixer.git
```

```bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```


```bash
cmake --build build
```
## Vai gerar um executável chamado Jogo em build ou build/debug 

```bash
./build/Debug/Jogo
```







