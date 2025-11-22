#!/usr/bin/env python3

import os
import platform
import subprocess
import misc


def runTestsOnLinux():
    os.chdir("bin")
    subprocess.run(
        "./tests-mcutils --gtest_filter=* --gtest_break_on_failure",
        shell=True
    )


def runTestsOnWindows():
    os.chdir("bin")
    subprocess.run(
        "tests-mcutils.exe --gtest_filter=* --gtest_break_on_failure",
        shell=True
    )


if __name__ == "__main__":
    misc.printGreen("Running tests...")
    os.chdir("..")
    os_name = platform.system()
    if os_name == "Linux":
        runTestsOnLinux()
    elif os_name == "Windows":
        runTestsOnWindows()
    misc.printGreen("Running tests done.")
