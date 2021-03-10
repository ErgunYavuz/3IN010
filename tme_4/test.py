u = ["test", "hello", "doggo"]
t = " "

for i in u:
    for l in i:
        if l not in t:
            print("before break")
            break
            print("after break")
        print("not in if")   