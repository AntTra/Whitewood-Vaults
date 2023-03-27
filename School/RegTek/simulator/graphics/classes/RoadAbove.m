classdef RoadAbove < handle
  properties (SetAccess=private)    
    % https://www.vegvesen.no/globalassets/fag/handboker/hb-n302.pdf
    RoadLength          = 60;   % [m]
    LaneWidth           = 4;  % [m]
    StripeWidth         = 0.15;  % [m]
    StripeLength        = 3;    % [m]
    StripeSeparation    = 9;    % [m]

    StripeOffset;               % List of stripe offsets

    X = 0;                      % [m]

    Road    = gobjects(1);
    Stripes = gobjects(1);
  end
  %
  % Public methods
  methods
    function obj = RoadAbove()
      obj.createGeometry();
      obj.updateTransforms();
    end
    function setStates(obj, x)
        obj.X           = x;
        obj.updateTransforms();
    end
    function r = isAlive(obj)
    % Call this to check whether the figure window is still alive.
      r = isvalid(obj) && isvalid(obj.Road);
    end
  end
  %
  % Private methods
  methods (Access=private)
    function createGeometry(obj)        
        obj.Road = patch([-obj.RoadLength, -obj.RoadLength, obj.RoadLength, obj.RoadLength],[-obj.LaneWidth, obj.LaneWidth, obj.LaneWidth, -obj.LaneWidth], 'k','FaceColor' ,[0.5 0.5 0.5]);
        
        obj.StripeOffset = -obj.RoadLength:obj.StripeLength+obj.StripeSeparation:obj.RoadLength;

        xStripe =   obj.StripeOffset+[-obj.StripeLength, -obj.StripeLength, obj.StripeLength, obj.StripeLength]'/2;
        yStripe = 0*obj.StripeOffset+[-obj.StripeWidth, obj.StripeWidth, obj.StripeWidth, -obj.StripeWidth]'/2;

        obj.Stripes = patch(xStripe,yStripe,'y','EdgeColor' ,'none');

    end

    function updateTransforms(obj)     
        obj.Road.XData = obj.X+[-obj.RoadLength, -obj.RoadLength, obj.RoadLength, obj.RoadLength];
        obj.Stripes.XData = (obj.StripeLength+obj.StripeSeparation)*round(obj.X/(obj.StripeLength+obj.StripeSeparation))+obj.StripeOffset+[-obj.StripeLength, -obj.StripeLength, obj.StripeLength, obj.StripeLength]'/2;
    end
  end
end