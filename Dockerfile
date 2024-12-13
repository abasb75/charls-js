FROM emscripten/emsdk:latest

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# default username, userid and group id to use in the container.
# NOTE - scripts/docker-build.sh overrides these using current user info via command line args
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Configure apt and install packages
RUN apt-get update \
    #
    # Install nvm 
    && su - $USERNAME -c "curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash" \
    #
    # Install C++ tools
    && apt-get -y install build-essential \
    #
    # version 3.17 of cmake
    #& wget -qO- "https://cmake.org/files/v3.17/cmake-3.17.0-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local\
    #
    # Clean up
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN npm install typescript tsc -v

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog