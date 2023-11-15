FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Install necessary dependencies
RUN apt-get update && \
    apt-get install -y git cmake make build-essential ninja-build gcc g++ libgmp-dev libssl-dev curl zip unzip tar pkg-config python3 libcurl4-openssl-dev linux-headers-$(uname -r)

ARG SSH_PRIVATE_KEY
RUN mkdir -p /root/.ssh && \
    echo "$SSH_PRIVATE_KEY" > /root/.ssh/id_rsa && \
    chmod 600 /root/.ssh/id_rsa && \
    ssh-keyscan github.com >> /root/.ssh/known_hosts

# Clone your Git repository

RUN git clone git@github.com:Blade-Labs/cpp-blade-demoapp.git .

RUN git submodule update --init

RUN ./vcpkg/bootstrap-vcpkg.sh

RUN cmake --preset linux-x64-release

RUN cmake --build --preset linux-x64-release

RUN cd package/bin

CMD ["./demo-application"]

