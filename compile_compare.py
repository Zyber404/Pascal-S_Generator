import subprocess


print("Generating test.pas ...")
subprocess.run("build/codegen > input/test.pas", shell=True)
print("Compiling test.pas to test.c ...")
subprocess.run("compiler/pascc -i input/test.pas", shell=True)
print("Compiling test.c ...")
subprocess.run("gcc -o output/c_test input/test.c", shell=True)
print("Compiling test.pas ...")
subprocess.run("fpc -gw3 -ooutput/pas_test input/test.pas", shell=True, capture_output=True)
c_out = subprocess.run("output/c_test", capture_output=True, text=True)
pas_out = subprocess.run("output/pas_test", capture_output=True, text=True)
if pas_out.stderr.startswith("Runtime error"):
    print(pas_out.stderr)
    quit()
line_count, true_count = 0, 0
for c_line, pas_line in zip(c_out.stdout.splitlines(), pas_out.stdout.splitlines()):
    line_count += 1
    if pas_line == "TRUE":
        pas_line = "1"
    if pas_line == "FALSE":
        pas_line = "0"
    if(not c_line.isalpha()):
        c_line = eval(c_line)
        pas_line = eval(pas_line)
    if type(c_line) == float:
        if abs(c_line - pas_line) <= abs(c_line/100):
            print("Match!")
            true_count +=1
        else:
            print(c_line,pas_line)
    elif c_line == pas_line:
        print("Match!")
        true_count +=1
    else:
        print(c_line,pas_line)
print("------------------------")
if line_count == true_count:
    print("All match!!!")
else:
    print("Not all match!!!")