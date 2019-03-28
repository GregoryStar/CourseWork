import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class kcluster {
    static int[][] dimMat;
    static double[][] magMat;
    static int[] vectorClass;
    static int[] actualClassLabels;
    static List<Integer> idOrderList;

    static double bestObjectiveValue;
    static double[][] bestCentroids;
    static int[] bestClassification;
    static int[][] outputMatrix;
    static int numActualCluster = 20;

    static Map<String, Integer> classMap;

    //Centroid data
    static double[][] centroids;

    static int numDimsInSpace = -1;

    //Input parameters
    static String inputFile;
    static String outputFile;
    static String classFile;
    static int numClusters;
    static int numTrials;
    static String criterionFunction;
    static int[] seedArray;

    public static void main(String[] args) {
        if(args.length == 6){
            inputFile = args[0];
            criterionFunction = args[1];
            classFile = args[2];
            numClusters = Integer.parseInt(args[3]);
            numTrials = Integer.parseInt(args[4]);
            outputFile = args[5];
        } else {
            //Run the program with pre-set test values
            System.out.println("Not enough arguments provided! Using default arguments for testing purposes...");
            inputFile = "log2freq.csv";
            criterionFunction = "SSE";
            classFile = "reuters21578.class";
            numClusters = 60;
            numTrials = 20;
            outputFile = "output.txt";
        }

        classMap = new HashMap<String, Integer>();

        try{
            readData();
        } catch (IOException e) {

        }

        numDimsInSpace++;
        seedArray = new int[] {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39};
        centroids = new double[numClusters][numDimsInSpace];
        vectorClass = new int[dimMat.length];
        outputMatrix = new int[numClusters][numActualCluster];

        bestCentroids = new double[numClusters][numDimsInSpace];

        long startTime = System.currentTimeMillis();
        bestClassification = new int[dimMat.length];
        if(criterionFunction.equalsIgnoreCase("SSE")){
            bestObjectiveValue = Double.MAX_VALUE;
            performKMeans();
        } else if(criterionFunction.equalsIgnoreCase("I2")){
            bestObjectiveValue = Double.MIN_VALUE;
            performSphericalKMeans();
        } else {
            System.out.println("Invalid criterion function!");
        }
        long endTime = System.currentTimeMillis();


        //Create the output matrix, so that entropy and purity may be easily computed
        for(int i = 0; i < numClusters; i++){
            for(int j = 0; j < numActualCluster; j++){
                int classCount = 0;
                for(int k = 0; k < vectorClass.length; k++){
                    if(bestClassification[k] == i && actualClassLabels[k] == j){
                        classCount++;
                    }
                }
                outputMatrix[i][j] = classCount;
            }
        }


        //Print the output matrix
        System.out.println("Output matrix (rows are clusters, columns are classes): ");
        for(int i = 0; i < outputMatrix.length; i++){
            String toPrint = "Cluster " + i + ": ";
            for(int j = 0; j < outputMatrix[i].length; j++){
                toPrint += outputMatrix[i][j];
                if(j < outputMatrix[i].length - 1){
                    toPrint += ",";
                }
            }
            System.out.println(toPrint);
        }

        //Print the centroids
        //System.out.println("Centroids found: ");
        //for(int i = 0; i < centroids.length; i++){
        //    for(int j = 0; j < centroids[i].length; j++)
        //}

        //Compute purity
        double[] rowPurities = new double[outputMatrix.length];
        double[] clusterCounts = new double[outputMatrix.length];
        double[][] probabilityMatrix = new double[outputMatrix.length][numActualCluster];
        for(int i = 0; i < outputMatrix.length; i++){
            double clusterCount = 0;
            for(int j = 0; j < numActualCluster; j++){
                clusterCount += outputMatrix[i][j];
            }
            clusterCounts[i] = clusterCount;

            double maxProb = 0;
            for(int j = 0; j < numActualCluster; j++){
                double currentProb = (double)outputMatrix[i][j]/clusterCount;
                probabilityMatrix[i][j] = currentProb;
                if(currentProb > maxProb){
                    maxProb = currentProb;
                }
            }

            rowPurities[i] = maxProb;
        }

        double totalPurity = 0;
        for(int i = 0; i < outputMatrix.length; i++){
            totalPurity += (clusterCounts[i]/(double)vectorClass.length) * rowPurities[i];
        }

        //Compute Entropy
        double[] clusterEntropies = new double[outputMatrix.length];
        for(int i = 0; i < clusterEntropies.length; i++){
            for(int j = 0; j < outputMatrix[i].length; j++) {
                double pij = probabilityMatrix[i][j];
                if(pij != 0){
                    double entropyTerm = pij;
                    entropyTerm *= (Math.log(pij)/Math.log(2));
                    clusterEntropies[i] += entropyTerm;
                }

            }
        }

        double totalEntropy = 0;
        for(int i = 0; i < outputMatrix.length; i++){
            totalEntropy += (clusterCounts[i]/(double)vectorClass.length) * clusterEntropies[i];
        }

        totalEntropy *= -1;

        System.out.println("Total time taken (seconds): " + (double)(endTime - startTime)/1000);
        System.out.println("Best clustering objective value: " + bestObjectiveValue);
        System.out.println("Total purity: " + totalPurity);
        System.out.println("Total entropy: " + totalEntropy);
        try{
            writeData();
        } catch (IOException e){

        }
    }

    public static void writeData() throws IOException{
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile, false));
        for(int i = 0; i < bestClassification.length; i++){
            String currentLine = idOrderList.get(i) + "," + bestClassification[i];
            if(i < bestClassification.length - 1){
                currentLine += "\n";
            }
            writer.write(currentLine);
        }
        writer.close();
    }

    public static void readData() throws IOException{
        Scanner scanner = new Scanner(new File(inputFile));

        //We're gonna use an arraylist data structure to store these vectors,
        //and then at the end, put them into array structures for fast access
        List<List<Integer>> vectorDimData = new ArrayList<>();
        List<List<Double>> vectorMagData = new ArrayList<>();
        idOrderList = new ArrayList<Integer>();
        int currentVectorID = -1;
        while(scanner.hasNextLine()){
            String currentLine = scanner.nextLine();
            String[] splitByComma = currentLine.split(",");

            //The line should be in the format: id,dim#,dimContribution
            int id = Integer.parseInt(splitByComma[0]);
            int dim = Integer.parseInt(splitByComma[1]);
            if(dim > numDimsInSpace){
                numDimsInSpace = dim;
            }
            double dimContribution = Double.parseDouble(splitByComma[2]);

            if(id != currentVectorID) {
                idOrderList.add(id);
                currentVectorID = id;
                vectorDimData.add(new ArrayList<Integer>());
                vectorMagData.add(new ArrayList<Double>());
            }
            List<Integer> currentDimVector = vectorDimData.get(vectorDimData.size() - 1);
            List<Double> currentMagVector = vectorMagData.get(vectorMagData.size() - 1);
            currentDimVector.add(dim);
            currentMagVector.add(dimContribution);
        }

        idOrderList.add(currentVectorID);
        scanner.close();

        //Convert the arrayLists to array representations
        dimMat = new int[vectorDimData.size()][];
        magMat = new double[vectorMagData.size()][];
        for(int i = 0; i < dimMat.length; i++){
            List<Integer> currentDimVec = vectorDimData.get(i);
            List<Double> currentMagVec = vectorMagData.get(i);
            dimMat[i] = new int[currentDimVec.size()];
            magMat[i] = new double[currentMagVec.size()];
            for(int j = 0; j < dimMat[i].length; j++){
                dimMat[i][j] = currentDimVec.get(j);
                magMat[i][j] = currentMagVec.get(j);
            }
        }


        scanner = new Scanner(new File(classFile));
        actualClassLabels = new int[dimMat.length];
        int index = 0;
        int mappingNum = 1;
        while(scanner.hasNextLine()){
            String currentLine = scanner.nextLine();
            String[] splitByComma = currentLine.split(",");

            //The line should be in the format id,label
            String label = splitByComma[1];
            if(classMap.containsKey(label)){
                actualClassLabels[index] = classMap.get(label);
            } else {
                classMap.put(label, mappingNum);
                mappingNum++;
                actualClassLabels[index] = classMap.get(label);
            }
            index++;
        }


        //String toPrint = "";
        //for(int i = 0; i < actualClassLabels.length; i++){
        //    toPrint += actualClassLabels[i] + ",";
        //}
        //System.out.println(toPrint);




        scanner.close();
    }

    public static void performSphericalKMeans(){
        for(int trial = 0; trial < numTrials; trial++){
            long trialStart = System.currentTimeMillis();
            System.out.println("Performing Trial " + (trial + 1) + "/" + numTrials);
            initializeCentroids(trial);
            for(int i = 0; i < dimMat.length; i++){
                vectorClass[i] = -1;
            }


            //do not perform more than 10 iterations
            for(int iter = 0; iter < 10; iter++){
                for(int i = 0; i < dimMat.length; i++){
                    double bestGain = -1;
                    int bestClass = vectorClass[i];
                    double[] bestCentroid = new double[numDimsInSpace];
                    for(int j = 0; j < numClusters; j++){
                        //compute the objective function for all clusters that it's not already in
                        if(vectorClass[i] != j){
                            double oldLength = magnitude(centroids[j]);
                            double[] newCentroid = hypotheticalCentroidAdd(i, j);
                            double newLength = magnitude(newCentroid);

                            double lengthGain = newLength - oldLength;
                            if(lengthGain > bestGain){
                                bestGain = lengthGain;
                                bestClass = j;
                                bestCentroid = newCentroid;
                            }
                        }
                    }


                    double costOfSwappingClasses = 0;
                    if(vectorClass[i] != -1){
                        costOfSwappingClasses = magnitude(centroids[vectorClass[i]]) - magnitude(subtractCentroid(dimMat[i], magMat[i], centroids[vectorClass[i]]));
                    }

                    if(bestGain > costOfSwappingClasses){
                        vectorClass[i] = bestClass;
                        centroids[bestClass] = bestCentroid;
                    }
                }
                //double tempVal = sphericalKMeansObjective();
                //System.out.println("Objective value at iteration " + iter + ": " + tempVal);
            }

            long trialEnd = System.currentTimeMillis();
            System.out.println("Time taken for trial (seconds): " + (double)(trialEnd - trialStart)/1000);

            //Compute cost of this solution
            double objectiveFunctionVal = sphericalKMeansObjective();
            if(objectiveFunctionVal > bestObjectiveValue){
                bestObjectiveValue = objectiveFunctionVal;
                bestClassification = vectorClass;
                bestCentroids = centroids;
            }

            System.out.println("Objective value of this solution: " + objectiveFunctionVal);
        }
    }

    public static void performKMeans(){
        for(int trial = 0; trial < numTrials; trial++){
            long trialStart = System.currentTimeMillis();
            System.out.println("Performing Trial " + (trial + 1) + "/" + numTrials);
            initializeCentroids(trial);

            //do not perform more than 10 iterations
            for(int iter = 0; iter < 10; iter++){
                //For every point, determine its class
                for(int i = 0; i < dimMat.length; i++){
                    double minDistance = Double.MAX_VALUE;
                    int bestCluster = -1;
                    for(int j = 0; j < numClusters; j++){
                        double currentDistance = distanceToCentroid(i, j);
                        if(currentDistance < minDistance){
                            bestCluster = j;
                            minDistance = currentDistance;
                        }
                    }

                    //Classify the point as the bestCluster
                    vectorClass[i] = bestCluster;
                }

                //Wipe centroids
                for(int i = 0; i < centroids.length; i++){
                    centroids[i] = new double[numDimsInSpace];
                }

                //Recompute the centroids
                double[] numInClasses = new double[numClusters];
                for(int i = 0; i < dimMat.length; i++){
                    numInClasses[vectorClass[i]] += 1;
                    addToCentroid(i, vectorClass[i]);
                }

                //Divide centroids by the number of elements in the class
                for(int i = 0; i < numClusters; i++){
                    for(int j = 0; j < centroids[i].length; j++){
                        centroids[i][j] /= numInClasses[i];
                    }
                }

            }

            long trialEnd = System.currentTimeMillis();
            System.out.println("Time taken for trial (seconds): " + (double)(trialEnd - trialStart)/1000);

            //Compute cost of this solution
            double objectiveValue = kMeansObjective();


            if(objectiveValue < bestObjectiveValue){
                bestObjectiveValue = objectiveValue;
                bestClassification = vectorClass;
                bestCentroids = centroids;
            }

            System.out.println("Cost of this solution: " + objectiveValue);
        }
    }

    public static double kMeansObjective(){
        double objective = 0;
        for(int i = 0; i < dimMat.length; i++){
            double temp = distanceToCentroid(i, vectorClass[i]);
            objective += temp * temp;
        }
        return objective;
    }


    public static double sphericalKMeansObjective(){
        double objective = 0;
        for(int i = 0; i < numClusters; i++){
            objective += magnitude(centroids[i]);
        }
        return objective;
    }

    public static void initializeCentroids(int seedIndex){
        Random random = new Random(seedArray[seedIndex]);
        for(int i = 0; i < centroids.length; i++) {
            for (int j = 0; j < numDimsInSpace; j++) {
                centroids[i][j] = random.nextDouble();
            }
            normalize(centroids[i]);
        }
    }

    public static double magnitude(double[] vector){
        double magSum = 0;
        for(int i = 0; i < vector.length; i++){
            magSum += vector[i] * vector[i];
        }
        return Math.sqrt(magSum);
    }

    public static void normalize(double[] vector){
        double magnitude = magnitude(vector);
        for(int i = 0; i < vector.length; i++){
            vector[i] /= magnitude;
        }
    }

    public static double[] subtractCentroid(int[] dimVec, double[] magVec, double[] centroid){
        double[] result = new double[centroid.length];
        for(int i = 0; i < centroid.length; i++){
            result[i] = centroid[i];
        }

        for(int i = 0; i < dimVec.length; i++){
            result[dimVec[i]] -= magVec[i];
        }

        return result;
    }


    public static void addToCentroid(int vectorNum, int centroidNum){
        int[] dimVec = dimMat[vectorNum];
        double[] magVec = magMat[vectorNum];
        double[] centroid = centroids[centroidNum];

        for(int i = 0; i < dimVec.length; i++){
            centroid[dimVec[i]] += magVec[i];
        }
    }

    public static double[] hypotheticalCentroidAdd(int vectorNum, int centroidNum){
        int[] dimVec = dimMat[vectorNum];
        double[] magVec = magMat[vectorNum];
        double[] centroid = centroids[centroidNum];
        double[] tempCentroid = new double[centroid.length];
        for(int i = 0; i < tempCentroid.length; i++){
            tempCentroid[i] = centroid[i];
        }

        for(int i = 0; i < dimVec.length; i++){
            tempCentroid[dimVec[i]] += magVec[i];
        }

        return tempCentroid;
    }

    public static double distanceToCentroid(int vectorNum, int centroidNum){
        int[] dimVec = dimMat[vectorNum];
        double[] magVec = magMat[vectorNum];
        double[] centroid = centroids[centroidNum];
        return magnitude(subtractCentroid(dimVec, magVec, centroid));
    }



}

