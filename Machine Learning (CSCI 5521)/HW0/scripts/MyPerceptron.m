function [w, step] = MyPerceptron(X, y, w0)
    w = transpose(w0);
    tData = transpose(X);
    tLabels = transpose(y);
    step = 0;
    converged = false;
    xAxis = tData(1, :);
    yAxis = tData(2, :);
    

    %Create the initialization figure
    figure
    %x axis, y axis, group labels, group colors, group markers, group sizes, legend
    gscatter(xAxis, yAxis, tLabels, ['r' 'b'], '.', [], 'off');
    title('Initialization');
    hold on
    a = linspace(-10,10);
    b = -(w(1)*a)/w(2);
    plot(a, b, 'Color', [0,0,0]);
    axis([-1 1 -1 1]);
    hold off

    %stop when a full pass of the data occurs with no changes to w, 
    %or when this process exceeds 1000 operations
    while ~converged && step < 1000
        firstW = w;
        for i = 1:length(tData)
            dataPoint = transpose(tData(1:2, i));
            class = tLabels(i);
            step = step + 1;
            if dot(w, dataPoint) * class <= 0
                w = w + class * dataPoint;
            end 
        end
        if firstW == w
            converged = true;
        end
    end
    
    if converged
        figure
        gscatter(xAxis, yAxis, tLabels, ['r' 'b'], '.', [], 'off');
        title('When Perceptron Converges');
        hold on
        a = linspace(-10,10);
        b = -(w(1)*a)/w(2);
        plot(a, b, 'Color', [0,0,0]);
        axis([-1 1 -1 1]);
    else
        disp("Failed to converge after 1000 steps");
    end
    

    
    
end