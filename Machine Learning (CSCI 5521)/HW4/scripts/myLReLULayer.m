classdef myLReLULayer < nnet.layer.Layer
    properties (Learnable)

    end
    
    methods
        function layer = myLReLULayer(name) 
            % Set layer name
            if nargin == 1
                layer.Name = name;
            else
                layer.Name = "LReLULayer";
            end

            % Set layer description
            layer.Description = 'myLReLULayer'; 
        
        end
        
        function Z = predict(~, X)
            % Forward input data through the layer and output the result
            
            Z = max(0, X) + 0.01 * min(0, X);
        end
        
        function [dLdX] = backward(~, X, ~, dLdZ, ~)
            % Backward propagate the derivative of the loss function through 
            % the layer 
            
            dLdX = 0.01 * dLdZ;
            dLdX(X>0) = dLdZ(X>0);
        end
    end
end