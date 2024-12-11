import subprocess, shlex, platform


def call_commands(command):
    """
    Runs each command passed to function as if manually entered onto CLI
    """
    cmd = shlex.split(command)
    output = subprocess.check_output(cmd)
    return output


def setup_project():
    """
    Checks native operating system and passes appropriate commands to install required modules
    """

    system_type = platform.system()
    is_compatible = True
    is_windows = False
    # determine operating system for assigning appropriate commands and required packages
    match system_type:
        case "Windows":
            check_for_pip = f"py -m pip --version"
            install_pip = f"py -m ensurepip --default-pip"
            install_list = f"py pip install -r ./requirements/windows_requirements.txt"
            setup_script = f"powershell ./scripts/Windows/windows_setup.ps1"
            is_windows = True
        case "Linux":
            check_for_pip = f"python3 -m pip --version"
            install_pip = f"python3 -m ensurepip --default-pip"
            install_list = f"pip install -r ./requirements/linux_requirements.txt"
            setup_script = f"source ./scripts/Linux/venv_linux_setup.sh"
        case "Darwin":
            check_for_pip = f"python3 -m pip --version"
            install_pip = f"python3 -m ensurepip --default-pip"
            install_list = f"python3 pip install -r ./requirements/mac_requirements.txt"
            setup_script = f"source ./scripts/MacOS/venv_macOS_setup.sh"
        case _:
            is_compatible = False
            print("System {} detected. This program may not be compatible with your local machine OS".format(system_type))
            print("Please refer to README for further information on determining local OS comptability")

    if is_compatible:
        print("Checking for pip..")

        # Determine whether pip installer is present and attempt to install if not found
        try:
            call_commands(check_for_pip)
        except:
            print("pip installer not found.")
            print("Attempting to install pip...")
            try:
                call_commands(install_pip)
            except:
                print("Unable to install pip. Please visit to https://packaging.python.org/en/latest/tutorials/installing-packages/ to manually install pip")
                return
        print("Pip installer found! Attempting to install program requirements...")
        
        # Attempt to install all requirements specific to local machine's OS
        try:
            call_commands(install_list)
        except Exception as err:
            print(err.args)
            print("Not all requirements were able to succesfully updated or installed. Please view the printed errors above.")
        print("Success! All requirements have been installed or updated!")

        # # Attempt to run system-specific setup script to build CMake project
        # try:
        #     call_commands(setup_script)
        # except Exception as err:
        #     print(err.args)
        #     print("One or more error(s) were encountered while running the setup script. Please view the printed errors above.")
        

        # If windows user, notify user of need to download graphviz zip archive and place it in 'Graphviz' directory
        if is_windows:
            print("Windows system detected. This program requires additional setup for using the Graphviz program.\n"
                  "Please visit https://graphviz.org/download/ to download the most recent version Graphviz zip folder for Windows\n"
                  "and place its extracted contents (excluding the actual folder) within the 'Graphviz' directory of the cloned repository.\n"
                  "This will allow the program to utilize Graphviz and eliminates the need to complete additional setup/installation steps.")

if __name__ == "__main__":
    setup_project()