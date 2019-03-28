def DNA(sequence):
    start = "ATG"
    end = ["TAG", "TAA", "TGA"]
    done = False
    genes = []
    while not done:
        i = sequence.find(start)
        if i == -1 and len(sequence) > 3:
            done = True
        else:
            j = i + 3
            listSeq = []
            while j < len(sequence) - 1:
                j += 3
                if j >= 3 and (len(sequence[j-3:j]) % 3 == 0):
                    listSeq.append(sequence[j - 3:j])
            x = 0
            notFound = True
            while notFound and x < len(listSeq):
                if listSeq[x] in end:
                    notFound = False
                else:
                    x += 1
            if notFound:
                done = True
            else:
                sequence = sequence[i + x*3:]
                gene = ""
                for string in listSeq[:x]:
                    gene += string
                genes.append(gene) 
    return genes

print(DNA("ATGAAAAAAAAATAGAAAATGAAATAACCCATGBBB"))
