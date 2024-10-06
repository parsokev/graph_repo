import subprocess, shlex, platform


def install_reqs(command):
    """
    Runs each command passed to function as if manually entered onto CLI
    """
    cmd = shlex.split(command)
    output = subprocess.check_output(cmd)
    return output


def install_dependencies():
    """
    Checks native operating system and passes appropriate commands to install required modules
    """

    system_type = platform.system()

    # determine operating system for appropriate commands
    if system_type != "Windows":
        check_for_pip = f"python3 -m pip --version"
        install_pip = f"python3 -m ensurepip --default-pip"
    else:
        check_for_pip = f"py -m pip --version"
        install_pip = f"py -m ensurepip --default-pip"

    print("Checking for pip..")

    # determine whether pip installer is present
    try:
        install_reqs(check_for_pip)
    except:
        print("pip installer not found.")
        print("Attempting to install pip...")
        try:
            install_reqs(install_pip)
        except:
            print("Unable to install pip. Please visit to https://packaging.python.org/en/latest/tutorials/installing-packages/ to manually install pip")
            return

    # if pip installer is confirmed, install necessary modules for application execution from requirements.txt
    with open("./graph_repo/windows_requirements.txt") as reqs:
        install_requires = reqs.read().splitlines()

        for req in install_requires:
            install_cmd = f"pip install {str(req)}"
            pkg = str(req).split(">=")
            print(f"Installing/Updating {pkg[0]}...")
            try:
                install_reqs(install_cmd)
            except:
                print(f"Error: There was a problem installing the {pkg[0]} module.")
                print("Please refer to the individual links in the README to manually install this module before proceeding further/")


if __name__ == "__main__":
    install_dependencies()