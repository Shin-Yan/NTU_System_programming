with open("FileSharing.txt", mode = 'w+') as fp:
    for i in range(1,101):
        fp.write(str(i))
        num_of_space = 9 - len(str(i))
        fp.write(num_of_space * " ")
        fp.write("\n")