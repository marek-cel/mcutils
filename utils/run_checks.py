#!/usr/bin/env python3

import os
import subprocess
import clean
import misc

build_dir = "build"
include_dir = "include/mcutils"
src_dir = "src"


def run_cloc():
    subprocess.run("cloc ./" + src_dir + "/* > out_cloc.txt", shell=True)


def run_cppcheck():
    command = "cppcheck"
    options = "--enable=style --std=c++17 -I ./" + src_dir + " ./" + src_dir
    subprocess.run(
        command + " " + options + " 2> out_cppcheck.txt",
        shell=True
    )


def run_clang_tidy():
    header_files = []
    for root, dirs, files in os.walk(include_dir):
        for file in files:
            if file.endswith('.h'):
                header_files.append(os.path.join(root, file))
    
    # Get all source files from src directory and subdirectories
    source_files = []
    for root, dirs, files in os.walk(src_dir):
        for file in files:
            if file.endswith('.cpp'):
                source_files.append(os.path.join(root, file))
    
    # Run clang-tidy on all files
    all_files = header_files + source_files

    for file in all_files:
        print(f"Running clang-tidy on {file}")

    checks = [
        "cppcoreguidelines-*"
    ]

    checks_str = ",".join(checks)

    for file in all_files:
        command = [
            "clang-tidy",
            f"-checks={checks_str}",
            f"-header-filter=.*",
            file,
            "--",
            f"-I{include_dir}"
        ]

        try:
            # Append output to file instead of overwriting
            with open("out_clang-tidy.txt", "a") as output_file:
                subprocess.run(
                    command,
                    stdout=output_file,
                    stderr=subprocess.STDOUT,
                    text=True
                )
        except subprocess.CalledProcessError as e:
            print(f"clang-tidy encountered an error for {file}: {e}")
        except FileNotFoundError:
            print("Error: clang-tidy not found. Please install clang-tidy.")
            break


def run_cpplint():
    filter = "-build/c++11,+build/c++14,+build/c++17" \
        + ",-readability/multiline_comment" \
        + ",-readability/alt_tokens" \
        + ",-whitespace,-legal/copyright" \
        + ",-build/include_order"
    cmd = "cpplint" \
        + " --filter=" + filter \
        + " --linelength=120" \
        + " --extensions=h,cpp" \
        + " --root=./" \
        + " ./" + include_dir + "/*.h" \
        + " ./" + include_dir + "/*/*.h" \
        + " ./" + src_dir + "/*.cpp" \
        + " ./" + src_dir + "/*/*.cpp" \
        + " 2> out_cpplint.txt"
    subprocess.run(cmd, shell=True)


def run_pycodestyle():
    for file in os.listdir("."):
        if file.endswith('.py'):
            command = "pycodestyle"
            options = "--show-source --show-pep8 --max-line-length=100"
            subprocess.run(
                command + " " + options + " " + file + " >> ../out_pep.txt",
                shell=True
            )


def runScanBuild():
    clean.removeBuildDirs()
    os.makedirs(build_dir)
    os.chdir(build_dir)
    cmd = [
        "cmake", "..",
        "-DCMAKE_BUILD_TYPE=Release"
    ]
    subprocess.run(cmd)
    subprocess.run("scan-build-10 -analyze-headers make -j 4", shell=True)


if __name__ == "__main__":
    clean.removeCheckOutputs()
    misc.printGreen("Running checks...")
    run_pycodestyle()
    os.chdir("..")
    run_cloc()
    run_cppcheck()
    run_clang_tidy()
    run_cpplint()
    misc.printGreen("Running checks done.")
