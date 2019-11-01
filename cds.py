import csv

file1 = open("Routemap_UttaraBus_tasfik.txt", "w")
ff = True
with open('Routemap-UttaraBus.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        ff = True
        ii = 0
        for data in row:
            if(ii >= len(row)-2):
                print(len(row))
                print(len(data))
                print()
                break
            if(ff):
                ff = False
            else:
                file1.write(data+'     ')
            ii = ii+1
        file1.write('$')
        file1.write('\n')

        line_count += 1
    print(f'Processed {line_count} lines.')
