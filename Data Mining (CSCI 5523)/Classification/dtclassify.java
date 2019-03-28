import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class dtclassify {
    static String modelFile;
    static String inputFile;
    static String outputFile;

    static int numDims;
    static int[] realClassLabels;
    static int[] predictedClassLabels;
    static float[][] dataSet;
    static BTree decisionTree;

    public static void main(String[] args) {
        if(args.length == 3){
            modelFile = args[0];
            inputFile = args[1];
            outputFile = args[2];
        } else {
            //Run the program with pre-set test values
            System.out.println("Not enough arguments provided! Using default arguments for testing purposes...");
            modelFile = "model.csv";
            inputFile = "data/rep1/test.csv";
            outputFile = "predictions.txt";
        }

        try{
            readData();
        } catch (IOException e){

        }

        predictedClassLabels = new int[dataSet.length];
        for(int i = 0; i < dataSet.length; i++){
            predictedClassLabels[i] = classify(dataSet[i], decisionTree);
        }

        try{
            writeData();
        } catch (IOException e){

        }
    }

    public static int classify(float[] dataPoint, BTree currentNode){
        if(currentNode.label != -1){
            return currentNode.label;
        } else {
            int splitFeature = currentNode.feature;
            float threshold = currentNode.threshold;
            if(dataPoint[splitFeature] <= threshold){
                return classify(dataPoint, currentNode.left);
            } else {
                return classify(dataPoint, currentNode.right);
            }
        }
    }

    public static void writeData() throws IOException{
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile, false));
        for(int i = 0; i < realClassLabels.length; i++){
            String line = realClassLabels[i] + " " + predictedClassLabels[i];
            if(i < predictedClassLabels.length - 1){
                line += "\n";
            }
            writer.write(line);
        }
        writer.close();
    }

    public static void readData() throws IOException {
        //READ THE MODEL IN
        Scanner scanner = new Scanner(new File(modelFile));

        List<BTree> preorderList = new ArrayList<BTree>();
        List<BTree> inorderList = new ArrayList<BTree>();
        boolean line1 = true;
        while(scanner.hasNextLine()){
            String currentLine = scanner.nextLine();
            String[] nodes = currentLine.split(" ");
            for(int i = 0; i < nodes.length; i++){
                String[] nodeElements = nodes[i].split(",");
                BTree currentNode = new BTree();

                int id = Integer.parseInt(nodeElements[0]);
                int label = Integer.parseInt(nodeElements[1]);
                currentNode.id = id;
                currentNode.label = label;

                if(label == -1){
                    currentNode.feature = Integer.parseInt(nodeElements[2]);
                    currentNode.threshold = Float.parseFloat(nodeElements[3]);
                }

                if(line1) {
                    preorderList.add(currentNode);
                } else {
                    inorderList.add(currentNode);
                }
            }
            line1 = false;
        }
        scanner.close();
        decisionTree = buildTree(preorderList, inorderList, 0, inorderList.size() - 1, 0, preorderList.size() - 1);

        //READ THE TEST SET IN
        scanner = new Scanner(new File(inputFile));

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
        realClassLabels = new int[classLabelList.size()];
        for(int i = 0; i < classLabelList.size(); i++){
            realClassLabels[i] = classLabelList.get(i);
        }

        dataSet = new float[dataSetList.size()][numDims];
        for(int i = 0; i < dataSetList.size(); i++){
            for(int j = 0; j < numDims; j++){
                dataSet[i][j] = dataSetList.get(i).get(j);
            }
        }
    }

    public static int findParent(BTree node, List<BTree> inorderList){
        int id = node.id;
        for(int i = 0; i < inorderList.size(); i++){
            if(inorderList.get(i).id == id){
                return i;
            }
        }

        return -1;
    }

    //is: inorder starting index, ie: inorder ending index, ps: preorder starting index, pe: preorder ending index
    public static BTree buildTree(List<BTree> preorderList, List<BTree> inorderList, int is, int ie, int ps, int pe){
        //If either of the starting indices are greater than the corresponding end index, we're done
        if(ps > pe || is > ie){
            return null;
        } else {
            BTree rootNode = preorderList.get(ps);
            int indexOfParent = findParent(rootNode, inorderList);

            BTree newNode = new BTree();
            newNode.id = rootNode.id;
            newNode.label = rootNode.label;
            if(newNode.label == -1){
                newNode.feature = rootNode.feature;
                newNode.threshold = rootNode.threshold;
            }

            newNode.left = buildTree(preorderList, inorderList, is, indexOfParent - 1, ps + 1, ps - is + indexOfParent);
            newNode.right = buildTree(preorderList, inorderList, indexOfParent + 1, ie, ps - is + indexOfParent + 1, pe);

            return newNode;
        }
    }
}

class BTree {
    public BTree left;
    public BTree right;

    //Data
    public int id;
    public int label = -1;
    public int feature;
    public float threshold;
}
