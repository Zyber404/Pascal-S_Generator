import subprocess
import os
from tqdm import tqdm

total_num = 0
total_true = 0
for i in tqdm(range(500)):
    subprocess.run("build/codegen > input/test.pas", shell=True)
    subprocess.run("compiler/pascc -i input/test.pas", shell=True)
    # output/c_test不存在，跳过
    subprocess.run("gcc -o output/c_test input/test.c", shell=True)
    if not os.path.exists("output/c_test"):
        continue
    subprocess.run("fpc -ooutput/pas_test input/test.pas", shell=True, capture_output=True)
    c_out = subprocess.run("output/c_test", capture_output=True, text=True)
    pas_out = subprocess.run("output/pas_test", capture_output=True, text=True)
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
                # print("Match!")
                true_count +=1
            else:
                print(c_line,pas_line)
        elif c_line == pas_line:
            # print("Match!")
            true_count +=1
        else:
            print(c_line,pas_line)
    # print("------------------------")
    if line_count == true_count:
        # print("All match!!!")
        total_true += 1
        total_num += 1
    else:
        # print("Not all match!!!")
        total_num += 1
print("Total: ", total_num, "True: ", total_true, "Accuracy: ", total_true/total_num)