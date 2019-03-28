import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class showconfmatrix {
    static String predictionFile;

    static int[] realClassLabels;
    static int[] predictedClassLabels;

    public static void main(String[] args) {
        if(args.length == 1){
            predictionFile = args[0];
        } else {
            //Run the program with pre-set test values
            System.out.println("Not enough arguments provided! Using default arguments for testing purposes...");
            predictionFile = "predictions.txt";
        }

        try{
            readData();
        } catch (IOException e){

        }

        int[][] confusionMatrix = new int[10][10];
        for(int i = 0; i < realClassLabels.length; i++){
            confusionMatrix[realClassLabels[i]][predictedClassLabels[i]] += 1;
        }

        System.out.println("Confusion Matrix: ");
        for(int i = 0; i < 10; i++){
            String line = "";
            for(int j = 0; j < 10; j++){
                line += String.format("%-5d ", confusionMatrix[i][j]);
            }
            System.out.println(line);
        }

        float numCorrect = 0;
        for(int i = 0; i < predictedClassLabels.length; i++){
            if(predictedClassLabels[i] == realClassLabels[i]){
                numCorrect += 1;
            }
        }

        float accuracy = numCorrect/(float)predictedClassLabels.length;
        System.out.println("Accuracy: " + accuracy);
    }

    public static void readData() throws IOException {
        Scanner scanner = new Scanner(new File(predictionFile));

        List<Integer> realClassLabelList = new ArrayList<Integer>();
        List<Integer> predictedClassLabelList = new ArrayList<Integer>();
        while(scanner.hasNextLine()){
            String currentLine = scanner.nextLine();
            String[] splitBySpace = currentLine.split(" ");

            realClassLabelList.add(Integer.parseInt(splitBySpace[0]));
            predictedClassLabelList.add(Integer.parseInt(splitBySpace[1]));
        }
        scanner.close();

        //Convert the arraylists to arrays, for fast access
        realClassLabels = new int[realClassLabelList.size()];
        for(int i = 0; i < realClassLabelList.size(); i++){
            realClassLabels[i] = realClassLabelList.get(i);
        }

        predictedClassLabels = new int[predictedClassLabelList.size()];
        for(int i = 0; i < predictedClassLabelList.size(); i++){
            predictedClassLabels[i] = predictedClassLabelList.get(i);
        }
    }
}
