import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class dtinduce {
    static String inputFile;
    static int minFreq;
    static String outputFile;

    static int[] classLabels;
    static float[][] dataSet;
    static int numDims;
    static Set<Integer> usedFeatures;
    static BinaryTree decisionTree;

    static int totalMembersAccountedFor = 0;
    static int nodeID = 0;

    //This is perhaps an ugly use of globals, but it allows for efficient code without introducing
    //a bunch of OOP, which I'm trying to avoid because of the makefile...
    static float[][] classCountMat;
    static float[] currentThresholds;
    static float[] currentGinis;

    static StringBuilder preorderBuilder;
    static StringBuilder inorderBuilder;

    public static void main(String[] args) {
        if(args.length == 3){
            inputFile = args[0];
            minFreq = Integer.parseInt(args[1]);
            outputFile = args[2];
        } else {
            //Run the program with pre-set test values
            System.out.println("Not enough arguments provided! Using default arguments for testing purposes...");
            inputFile = "data/rep1/train.csv";
            minFreq = 10;
            outputFile = "model.csv";
        }

        //Read the data in from the input file
        System.out.println("Reading data from file...");
        try{
            readData();
        } catch (IOException e){

        }
        currentGinis = new float[numDims];
        currentThresholds = new float[numDims];

        usedFeatures = new HashSet<Integer>();
        decisionTree = new BinaryTree();

        //Initialize the set in the decision tree
        List<Integer> allData = new ArrayList<Integer>();
        for(int i = 0; i < dataSet.length; i++){
            allData.add(i);
        }
        decisionTree.set = allData;

        //Train the decision tree
        System.out.println("Training decision tree...");
        long startTime = System.currentTimeMillis();
        createDecisionTree(decisionTree);
        long endTime = System.currentTimeMillis();

        preorderBuilder = new StringBuilder();
        inorderBuilder = new StringBuilder();
        System.out.println("Performing preorder traversal of tree...");
        traversePreorder(decisionTree);

        System.out.println("Performing inorder traversal of tree...");
        traverseInorder(decisionTree);

        System.out.println("Writing to file...");
        try{
            writeData();
        } catch (IOException e){

        }

        System.out.println("All Done");
        System.out.println("Total time taken (seconds): " + (double)(endTime - startTime)/1000);

    }

    public static void traversePreorder(BinaryTree currentNode){
        if(currentNode.label == -1){
            preorderBuilder.append(currentNode.id);
            preorderBuilder.append(",");
            preorderBuilder.append(currentNode.label);
            preorderBuilder.append(",");
            preorderBuilder.append(currentNode.feature);
            preorderBuilder.append(",");
            preorderBuilder.append(currentNode.threshold);
            preorderBuilder.append(" ");

            traversePreorder(currentNode.left);
            traversePreorder(currentNode.right);
        } else {
            preorderBuilder.append(currentNode.id);
            preorderBuilder.append(",");
            preorderBuilder.append(currentNode.label);
            preorderBuilder.append(" ");
        }
    }

    public static void traverseInorder(BinaryTree currentNode){
        if(currentNode.label == -1){
            traverseInorder(currentNode.left);

            inorderBuilder.append(currentNode.id);
            inorderBuilder.append(",");
            inorderBuilder.append(currentNode.label);
            inorderBuilder.append(",");
            inorderBuilder.append(currentNode.feature);
            inorderBuilder.append(",");
            inorderBuilder.append(currentNode.threshold);
            inorderBuilder.append(" ");

            traverseInorder(currentNode.right);
        } else {
            inorderBuilder.append(currentNode.id);
            inorderBuilder.append(",");
            inorderBuilder.append(currentNode.label);
            inorderBuilder.append(" ");
        }
    }

    public static void createDecisionTree(BinaryTree currentNode){
        List<Integer> setMembers = currentNode.set;

        //Ensures every node has a unique ID, which will be important when storing these nodes to a file
        currentNode.id = nodeID;
        nodeID++;

        //This checks the cutoff condition (when a node is considered finished)
        if(setMembers.size() < minFreq || usedFeatures.size() == numDims || isNodePure(setMembers)){
            totalMembersAccountedFor += setMembers.size();
            currentNode.label = computeLabel(setMembers);
            return;
        }

        //Reset the ginis
        for(int i = 0; i < currentGinis.length; i++){
            currentGinis[i] = Float.MAX_VALUE;
        }

        float bestGini = Float.MAX_VALUE;
        int bestFeature = -1;
        boolean[] absoluteBestSplit = new boolean[setMembers.size()];
        for(int i = 0; i < numDims; i++){
            if(!usedFeatures.contains(i)){
                boolean[] bestSplitForFeature = computeBestSplitOnFeature(i, setMembers);

                //Get the Gini index of the current feature which was computed already in computeBestSplitOnFeature
                float currentGini = currentGinis[i];

                if (currentGini <= bestGini) {
                    bestGini = currentGini;
                    bestFeature = i;
                    absoluteBestSplit = bestSplitForFeature;
                }
            }
        }
        usedFeatures.add(bestFeature);

        List<Integer> upperSplit = new ArrayList<Integer>();
        List<Integer> lowerSplit = new ArrayList<Integer>();
        for(int i = 0; i < setMembers.size(); i++){
            if(absoluteBestSplit[i]){
                upperSplit.add(setMembers.get(i));
            } else {
                lowerSplit.add(setMembers.get(i));
            }
        }

        //Now we must add this new threshold and feature to the binary tree
        currentNode.threshold = currentThresholds[bestFeature];
        currentNode.feature = bestFeature;

        //Since this is a splitting node, we don't need to keep the set inside of it
        currentNode.set = null;


        //NOTE: Doing one node at a time like this saves space since most nodes will not end up having
        //Any actual data inside of them.

        //Initialize the left node and compute it
        currentNode.left = new BinaryTree();
        currentNode.left.set = lowerSplit;
        createDecisionTree(currentNode.left);

        //Initialize the right node and compute it
        currentNode.right = new BinaryTree();
        currentNode.right.set = upperSplit;
        createDecisionTree(currentNode.right);

        usedFeatures.remove(bestFeature);
    }

    public static boolean isNodePure(List<Integer> setMembers){
        int firstClass = classLabels[setMembers.get(0)];
        for(Integer currentIndex : setMembers){
            if(classLabels[currentIndex] != firstClass){
                return false;
            }
        }
        return true;
    }

    public static int computeLabel(List<Integer> setMembers){
        int[] classCount = new int[10];
        for(Integer currentIndex : setMembers){
            classCount[classLabels[currentIndex]] += 1;
        }

        int label = -1;
        int currentMaxNum = -1;
        for(int i = 0; i < classCount.length; i++){
            if(currentMaxNum < classCount[i]){
                currentMaxNum = classCount[i];
                label = i;
            }
        }

        return label;
    }

    public static boolean[] computeBestSplitOnFeature(int feature, List<Integer> setMembers){
        //Get a sorted representation of the column associated with the split feature
        //TODO: PRESORT THE COLUMNS, BUT FOR NOW THIS IS FAST ENOUGH
        List<Float> featureColumn = new ArrayList<Float>();
        Map<Float, List<Integer>> thresholdToSetIndex = new HashMap<Float, List<Integer>>();
        for(int i = 0; i < setMembers.size(); i++){
            float currThreshold = dataSet[setMembers.get(i)][feature];
            if(thresholdToSetIndex.containsKey(currThreshold)){
                thresholdToSetIndex.get(currThreshold).add(i);
            } else {
                List<Integer> value = new ArrayList<Integer>();
                value.add(i);
                thresholdToSetIndex.put(currThreshold, value);
            }
            featureColumn.add(currThreshold);
        }
        Collections.sort(featureColumn);

        //Now we will split by each value in the feature column
        float bestGini = Float.MAX_VALUE;

        //false indicates under, true indicates over
        //NOTE: Everything starts in the under set; we will work through thresholds in reverse order
        boolean[] setMarker = new boolean[setMembers.size()];
        boolean[] bestSet = setMarker;

        classCountMat = new float[2][10];
        //Define the class count matrix (all values belong to the under set)
        for(int i = 0; i < setMembers.size(); i++){
            classCountMat[0][classLabels[setMembers.get(i)]] += 1;
        }

        //Shift things over from the underset to the overset and compute ginis for each new combo
        int i = featureColumn.size() - 1;
        while(i > 0){
            float threshold = featureColumn.get(i);

            //Move all values with the current threshold into the overset
            List<Integer> indicesToFlip = thresholdToSetIndex.get(threshold);
            for(int indexToFlip : indicesToFlip){
                setMarker[indexToFlip] = true;
                classCountMat[0][classLabels[setMembers.get(indexToFlip)]] -= 1;
                classCountMat[1][classLabels[setMembers.get(indexToFlip)]] += 1;
                i--;
            }

            if(i < 0){
                break;
            }

            float currentGini = computeGiniIndex(setMarker, i + 1);

            if(currentGini < bestGini){
                bestGini = currentGini;
                currentThresholds[feature] = threshold;
                currentGinis[feature] = bestGini;
                bestSet = Arrays.copyOf(setMarker, setMarker.length);
            }
        }

        return bestSet;
    }

    public static float computeGiniIndex(boolean[] setMarker, float underThresholdSize){
        float overThresholdSize = setMarker.length - underThresholdSize;
        float giniIndexUnder = 0;
        float giniIndexOver = 0;

        //Now compute the Gini index for the over and under set using the count matrix
        for(int i = 0; i < 10; i++){
            float probOfClassInUnderSet = classCountMat[0][i]/underThresholdSize;
            float probOfClassInOverSet = classCountMat[1][i]/overThresholdSize;

            giniIndexUnder += probOfClassInUnderSet * probOfClassInUnderSet;
            giniIndexOver += probOfClassInOverSet * probOfClassInOverSet;
        }
        giniIndexUnder = 1 - giniIndexUnder;
        giniIndexOver = 1 - giniIndexOver;

        //Finally, get the combined gini index, which is a weighted sum (divided by n, but n is constant
        //so we don't have to do that).
        float giniIndex = underThresholdSize * giniIndexUnder + overThresholdSize * giniIndexOver;

        return giniIndex;
    }

    public static void readData() throws IOException {
        Scanner scanner = new Scanner(new File(inputFile));

        List<Integer> classLabelList = new ArrayList<Integer>();
        List<List<Float>> dataSetList = new ArrayList<List<Float>>();
        while(scanner.hasNextLine()){
            String currentLine = scanner.nextLine();
            String[] splitByComma = currentLine.split(",");
            numDims = splitByComma.length - 1;

            classLabelList.add(Integer.parseInt(splitByComma[0]));
            ArrayList<Float> currentDatum = new ArrayList<Float>();
            for(int i = 1; i < splitByComma.length; i++){
                currentDatum.add(Float.parseFloat(splitByComma[i]));
            }
            dataSetList.add(currentDatum);
        }
        scanner.close();

        //Convert the arraylists to arrays, for fast access
        classLabels = new int[classLabelList.size()];
        for(int i = 0; i < classLabelList.size(); i++){
            classLabels[i] = classLabelList.get(i);
        }

        dataSet = new float[dataSetList.size()][numDims];
        for(int i = 0; i < dataSetList.size(); i++){
            for(int j = 0; j < numDims; j++){
                dataSet[i][j] = dataSetList.get(i).get(j);
            }
        }
    }

    public static void writeData() throws IOException{
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile, false));
        writer.write(preorderBuilder.toString());
        writer.write("\n");
        writer.write(inorderBuilder.toString());
        writer.close();
    }
}

class BinaryTree {
    public BinaryTree left;
    public BinaryTree right;

    //Data
    public int id;
    public int label = -1;
    public int feature;
    public float threshold;
    public List<Integer> set;
}
