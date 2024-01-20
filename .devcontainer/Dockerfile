FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

RUN \
    sudo apt-get update \
    && sudo apt-get install -y build-essential lldb gdb ninja-build libgtest-dev wget curl software-properties-common \
    # bring in latest cmake
    && sudo wget -qO /etc/apt/trusted.gpg.d/kitware-key.asc https://apt.kitware.com/keys/kitware-archive-latest.asc \ 
    && echo "deb https://apt.kitware.com/ubuntu/ focal main" | sudo tee /etc/apt/sources.list.d/kitware.list \
    && sudo add-apt-repository -y ppa:system76/pop \
    && sudo apt-get update \
    && sudo apt-get install -y cmake \
    # bring in latest clang toolchain
    && wget https://apt.llvm.org/llvm.sh \
    && chmod +x llvm.sh \
    && sudo ./llvm.sh 16 all \
    && rm llvm.sh \
    # install google chrome
    && sudo apt-get install -y fonts-liberation libasound2 libatk-bridge2.0-0 libatk1.0-0 libatspi2.0-0 libcairo2 libcups2\
    libdrm2 libgbm1 libgtk-3-0 libnspr4 libnss3 libpango-1.0-0 libu2f-udev libvulkan1 libxss1 libx11-6 libxcb1 libxcomposite1\
    libxdamage1 libxext6 libxfixes3 libxkbcommon0 libxrandr2 xdg-utils \
    && sudo wget -q https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb \
    && sudo dpkg -i google-chrome-stable_current_amd64.deb \
    && sudo rm ./google-chrome-stable_current_amd64.deb \ 
    # install latest nodejs
    && sudo apt-get install -y ca-certificates curl gnupg \
    && sudo curl -fsSL https://deb.nodesource.com/gpgkey/nodesource-repo.gpg.key | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/nodesource.gpg \
    && NODE_MAJOR=20 \
    && echo "deb [signed-by=/etc/apt/trusted.gpg.d/nodesource.gpg] https://deb.nodesource.com/node_$NODE_MAJOR.x nodistro main" | sudo  tee /etc/apt/sources.list.d/nodesource.list \
    && sudo apt-get update \
    && sudo apt-get install -y nodejs \
    && sudo npm install -g @marp-team/marp-cli \
    # Install the Catch2 testing framework
    && cd /usr/src && git clone --depth 1 --branch v3.4.0 https://github.com/catchorg/Catch2.git catch2 \
    && cd catch2 \
    && cmake -B build -DBUILD_TESTING=OFF \
             -D CMAKE_INSTALL_PREFIX=/usr \
             -GNinja \
    && cmake --build build \
    && cmake --install build \
    && cd /usr/src \
    && rm -rf catch2 \
    # Install python venv
    && sudo apt-get install python3-venv \
    # clean up
    && sudo rm -rf /var/lib/apt/lists/*