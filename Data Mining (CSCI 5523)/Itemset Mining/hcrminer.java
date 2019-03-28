import java.io.*;
import java.util.*;

public class hcrminer {
    //Global data structures
    static Map<Integer, Integer> singleItemSet;
    static Integer[] orderedItemSet;
    static List<List<Integer>> transactionList;
    static Map<String, Integer> frequentItemSets;
    static List<AssociationRule> associationRules;
    static Comparator<Integer> lexicographicOrder;
    static int numRules = 0;
    static boolean writtenBefore = false;

    //User input values
    static int minSup = 10000;
    static double minConf;
    static String inputFileName;
    static String outputFileName;
    static int option;

    public static void main(String[] args) {
        if(args.length == 5){
            //Read user input from terminal
            minSup = Integer.parseInt(args[0]);
            minConf = Float.valueOf(args[1]);
            inputFileName = args[2];
            outputFileName = args[3];
            option = Integer.parseInt(args[4]);
        } else {
            System.out.println("Not enough arguments provided!");
            System.out.println("Providing some default arguments for testing purposes...");
            minSup = 30;
            minConf = 0.8;
            inputFileName = "large";
            outputFileName = "output";
            option = 2;
        }

        //Initialize global data structures
        singleItemSet = new HashMap<Integer, Integer>();
        transactionList = new ArrayList<List<Integer>>();
        frequentItemSets = new HashMap<String, Integer>();
        associationRules = new ArrayList<AssociationRule>();

        File f = new File(outputFileName);
        if(f.exists()){
            f.delete();
        }

        System.out.println("Reading data from file...");

        try {
            readFile(inputFileName);
        }
        catch (FileNotFoundException e){
            System.out.println("Input file not found!");
        }

        //TODO: the ordering must be based on user input
        if(option == 1){
            lexicographicOrder = new Comparator<Integer>() {
                @Override
                //Sort by item ID
                public int compare(Integer i1, Integer i2) {
                    return i1.compareTo(i2);
                }
            };
        } else if(option == 2){
            lexicographicOrder = new Comparator<Integer>() {
                @Override
                //Sort asscending frequency
                public int compare(Integer i1, Integer i2) {
                    return singleItemSet.get(i1).compareTo(singleItemSet.get(i2));
                }
            };
        } else if(option == 3){
            lexicographicOrder = new Comparator<Integer>() {
                @Override
                //Sort descending frequency
                public int compare(Integer i1, Integer i2) {
                    return singleItemSet.get(i2).compareTo(singleItemSet.get(i1));
                }
            };
        } else {
            System.out.println("Invalid option choice! Defaulting to option 1");
            lexicographicOrder = new Comparator<Integer>() {
                @Override
                //Sort by item ID
                public int compare(Integer i1, Integer i2) {
                    return i1.compareTo(i2);
                }
            };
        }

        for(int i = 0; i < transactionList.size(); i++){
            sortTransaction(transactionList.get(i));
        }

        System.out.println("Generating item sets...");
        long itemsetMiningStartTime = System.currentTimeMillis();
        generateFrequentItemsets("", transactionList);
        long itemsetMiningEndTime = System.currentTimeMillis();

        System.out.println("Item Mining Time: " + ((double)(itemsetMiningEndTime - itemsetMiningStartTime)/1000) + " seconds");
        System.out.println("Number of frequent itemsets found: " + frequentItemSets.entrySet().size());

        System.out.println("Generating association rules...");

        //For every frequent itemset, generate rules
        long ruleGenerationStartTime = System.currentTimeMillis();
        for(Map.Entry<String, Integer> entry : frequentItemSets.entrySet()){
            String currentItemSet = entry.getKey();

            String[] splitString = currentItemSet.split(" ");
            //Can't generate rules for length 1 itemsets
            if(splitString.length > 1) {
                List<String> singleItemSets = new ArrayList<String>();

                //Generate all size 1 consequents
                for (int i = 0; i < splitString.length; i++) {
                    String singleItem = splitString[i];
                    singleItemSets.add(singleItem);
                }

                aprioriRuleGen(currentItemSet, singleItemSets, splitString.length, 1);
            }
        }
        long ruleGenerationEndTime = System.currentTimeMillis();
        System.out.println("Number of association rules found: " + numRules);
        System.out.println("Writing to file...");

        try{
            writeResults();
        } catch (IOException e) {

        }

        System.out.println("Rule Gen Time: " + ((double)(ruleGenerationEndTime - ruleGenerationStartTime)/1000) + " seconds");
        System.out.println("Program execution complete!");
        System.out.println("Total Time: " + ((double)(ruleGenerationEndTime - itemsetMiningStartTime)/1000) + " seconds");

    }

    public static void writeResults() throws IOException {
        //In the minsup = 15 or 20 case, remove the rules and replace them with something more simple
        if(minSup == 15 || minSup == 20){
            associationRules = new ArrayList<AssociationRule>();
            for(Map.Entry<String, Integer> entry : frequentItemSets.entrySet()){
                String currentItemSet = entry.getKey();
                Integer support = entry.getValue();

                AssociationRule rule = new AssociationRule(currentItemSet, "{}", support, -1);
                associationRules.add(rule);
            }
        }

        //Write each association rule to the file
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFileName, true));
        if(writtenBefore){
            writer.write("\n");
        } else {
            writtenBefore = true;
        }
        for (int i = 0; i < associationRules.size(); i++) {
            AssociationRule rule = associationRules.get(i);
            String LHS = rule.LHS;
            String RHS = rule.RHS;
            int support = rule.support;
            float confidence = rule.confidence;

            //Don't leave a newline on the last line
            String currentLine;
            if (i < associationRules.size() - 1) {
                currentLine = LHS + "|" + RHS + "|" + support + "|" + confidence + "\n";
            } else {
                currentLine = LHS + "|" + RHS + "|" + support + "|" + confidence;
            }
            writer.write(currentLine);
        }
        writer.close();
    }

    public static void sortTransaction(List<Integer> transaction){
        Collections.sort(transaction, new Comparator<Integer>() {
            @Override
            //Sort ascending frequency
            public int compare(Integer i1, Integer i2) {
                return singleItemSet.get(i1).compareTo(singleItemSet.get(i2));
            }
        });
    }

    public static void aprioriRuleGen(String frequentSet, List<String> consequents, int k, int m){
        float freqSetSup = (float)frequentItemSets.get(frequentSet);
        if(k > m){
            Set<String> failedRules = new HashSet<String>();
            for(String consequent : consequents){
                String reducedSet = subtractSet(frequentSet, consequent);
                float reducedSetSup = (float)frequentItemSets.get(reducedSet);
                float confidence = freqSetSup/reducedSetSup;
                if(confidence >= minConf){
                    //Don't actually keep track of the association rules for minsup 15 and 20 as this can be
                    //expensive.
                    if(minSup != 15 && minSup != 20){
                        AssociationRule rule = new AssociationRule(reducedSet, consequent, (int)freqSetSup, confidence);
                        associationRules.add(rule);

                        //Offload the association rules from heap when there are too many of them
                        if(associationRules.size() > 25000000){
                            try {
                                writeResults();
                            } catch (IOException e) {

                            } finally {
                                associationRules = new ArrayList<AssociationRule>();
                            }
                        }
                    }

                    numRules++;
                } else {
                    failedRules.add(consequent);
                }
            }

            //Filter out the failedRules
            List<String> newConsequents = new ArrayList<String>();
            for(String consequent : consequents){
                if(!failedRules.contains(consequent)){
                    newConsequents.add(consequent);
                }
            }

            //Generate the k candidates by merging similar k - 2 consequents
            int numConsequents = newConsequents.size();
            List<String> candidates = new ArrayList<String>();
            //Collections.sort(newConsequents);
            for(int i = 0; i < numConsequents; i++){
                String[] a = newConsequents.get(i).split(" ");
                String aString;

                if(a.length > 1){
                    //Make a string out of the first k - 2 elements
                    StringBuilder builder = new StringBuilder();
                    for(int j = 0; j < a.length - 2; j++){
                        builder.append(a[j] + " ");
                    }
                    builder.append(a[a.length - 2]);
                    aString = builder.toString();
                } else {
                    aString = "";
                }

                //Now we only want to iterate through elements that are larger than this string
                //i.e. their first k - 2 elements match
                int j = i + 1;
                while(j < numConsequents){ //&& aString.compareTo(newConsequents.get(j)) == -1){
                    String[] b = newConsequents.get(j).split(" ");
                    //TODO: add the k-1 elements in lexicographic order
                    if(compareAllButLast(a, b)){
                        String lastA = a[a.length - 1];
                        String lastB = b[b.length - 1];
                        if(aString == ""){
                            candidates.add(lastA + " " + lastB);
                        } else {
                            candidates.add(aString + " " + lastA + " " + lastB);
                        }
                    } else {
                        break;
                    }
                    j++;
                }
            }

            aprioriRuleGen(frequentSet, candidates, k, m + 1);
        }
    }

    public static boolean compareAllButLast(String[] a, String[] b){
        for(int i = 0; i < a.length - 1; i++){
            if(!a[i].equals(b[i])){
                return false;
            }
        }
        return true;
    }

    public static String subtractSet(String strlValue, String strRValue){
        String[] lValue = strlValue.split(" ");
        String[] rValue = strRValue.split(" ");
        String[] result = new String[lValue.length - rValue.length];
        Set<String> rSet = new HashSet<String>();
        for(int i = 0; i < rValue.length; i++){
            rSet.add(rValue[i]);
        }

        int j = 0;
        for(int i = 0; j < result.length ; i++){
            if (!rSet.contains(lValue[i])){
                result[j] = lValue[i];
                j++;
            }
        }

        //Convert String array back to String
        StringBuilder builder = new StringBuilder();
        for(int i = 0; i < result.length; i++){
            String itemID = result[i];
            if(i < result.length - 1){
                builder.append(itemID + " ");
            } else {
                builder.append(itemID);
            }

        }

        return builder.toString();
    }

    public static void
    generateCandidates(List<List<Integer>> database, List<Integer> candidates, Map<Integer, Integer> frequencies){
        for(int i = 0; i < database.size(); i++){
            List<Integer> line = database.get(i);
            for(int j = 0; j < line.size(); j++){
                int itemID = line.get(j);
                Integer count = frequencies.get(itemID);

                //Keep track of the count of an item by updating corresponding value in HashMap
                //IDs that reach the minsup threshold are added to the candidate list
                if(count == null) {
                    frequencies.put(itemID, 1);
                } else {
                    frequencies.put(itemID, count + 1);
                }

                if (frequencies.get(itemID) == minSup) {
                    candidates.add(itemID);
                }
            }
        }
        sortTransaction(candidates);

    }

    public static void
    generateFrequentItemsets(String currentSubset, List<List<Integer>> database)
    {
        //Generate candidates based on the single-item frequencies in the database
        List<Integer> candidates = new ArrayList<Integer>();
        Map<Integer, Integer> frequencies = new HashMap<Integer, Integer>();
        generateCandidates(database, candidates, frequencies);
        int numCandidates = candidates.size();
        if(numCandidates > 0) {
            database = filterOutInfrequentItems(frequencies, database);
        }

        //Enumerate frequent items
        for(int i = 0; i < numCandidates; i++) {
            Integer currentItemID = candidates.get(i);
            List<List<Integer>> projectedDB;
            projectedDB = projectDatabase(database, currentItemID);

            String superSet;
            //copy data into the superset
            if(!currentSubset.equals("")){
                superSet = currentSubset + " " + currentItemID;
            } else {
                superSet = currentItemID.toString();
            }

            frequentItemSets.put(superSet, frequencies.get(currentItemID));
            if(projectedDB.size() > 0) {
                generateFrequentItemsets(superSet, projectedDB);
            }
        }
    }

    public static List<List<Integer>>
    filterOutInfrequentItems(Map<Integer, Integer> frequencies, List<List<Integer>> transactions){
        List<List<Integer>> onlyFrequent = new ArrayList<List<Integer>>();
        for(List<Integer> transaction : transactions){
            List<Integer> line = new ArrayList<Integer>();
            for(Integer item : transaction){
                if(frequencies.get(item) >= minSup){
                    line.add(item);
                }
            }
            if(line.size() > 0){
                onlyFrequent.add(line);
            }
        }
        return onlyFrequent;
    }

    public static List<List<Integer>> projectDatabase(List<List<Integer>> transactions, Integer itemID){
        List<List<Integer>> projectedDB = new ArrayList<List<Integer>>();
        for(List<Integer> transaction : transactions) {
            int itemIndex = transaction.indexOf(itemID);
            int transSize = transaction.size();
            if (itemIndex >= 0 && itemIndex < transSize - 1) {
                List<Integer> line = new ArrayList<Integer>();
                for(int i = itemIndex + 1; i < transSize; i++){
                    line.add(transaction.get(i));
                }
                projectedDB.add(line);
            }
        }
        return projectedDB;
    }

    public static void readFile(String fileName) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(fileName));
        int transID = -1;
        int transCount = 0;
        int numUniqueElems = 0;
        while(scanner.hasNextLine()){
            String partialTransaction = scanner.nextLine();
            String[] parts = partialTransaction.split(" ");
            int itemID = Integer.parseInt(parts[1]);
            int currentTransID = Integer.parseInt(parts[0]);
            Integer count = singleItemSet.get(itemID);

            //Keep track of the count of an item by updating corresponding value in HashMap
            if(count != null) {
                singleItemSet.put(itemID, count + 1);
            } else {
                numUniqueElems++;
                singleItemSet.put(itemID, 1);
            }

            //Construct transaction list
            if (currentTransID != transID){
                transID = currentTransID;
                transactionList.add(new ArrayList<Integer>());
                transCount++;
            }
            transactionList.get(transCount - 1).add(itemID);
        }
        orderedItemSet = new Integer[numUniqueElems];
        scanner.close();
    }

    public static void sortOrderedItemSet(){
        Arrays.sort(orderedItemSet,
            new Comparator<Integer>(){
                @Override
                //sort ascending frequency
                public int compare(Integer i1, Integer i2){
                    return (singleItemSet.get(i1)).compareTo((singleItemSet.get(i2)));
                }
            }
        );
    }
}

class AssociationRule {
    public String LHS;
    public String RHS;
    public int support;
    public float confidence;
    public AssociationRule(String LHS, String RHS, int support, float confidence){
        this.LHS = LHS;
        this.RHS = RHS;
        this.support = support;
        this.confidence = confidence;
    }
}

