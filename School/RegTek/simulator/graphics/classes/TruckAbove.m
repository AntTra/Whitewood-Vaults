classdef TruckAbove < handle
  properties (SetAccess=private)    
    FilenameTruck       = 'truckAbove_truck.svg';
    FilenameLeftWheel   = 'truckAbove_left_wheel.svg';
    FilenameRightWheel  = 'truckAbove_right_wheel.svg';
    FilenameAnchor      = 'truckAbove_anchor.svg';

    SVGScalingFactor;
    XPixelMax = 0;
    XPixelMin = inf;

    TruckLength = 8;        % [m]

    % https://www.vegvesen.no/globalassets/fag/handboker/hb-n302.pdf
    RoadLength          = 200;  % [m]
    LaneWidth           = 3.5;  % [m]
    StripeWidth         = 0.1;  % [m]
    StripeLength        = 1;    % [m]
    StripeSeparation    = 3;    % [m]

    XAnchorPixels = 0;          % [pixels]
    YAnchorPixels = 0;          % [pixels]

    XAnchor = 0;                % [m]
    YAnchor = 0;                % [m]

    AngleTruck = 0;             % [rad]
    AngleWheels  = 0;           % [rad]

    Truck   = gobjects(1);
    Wheels  = gobjects(2);
    Trace   = gobjects(1);

    XLeftWheel;                 % [m]
    YLeftWheel;                 % [m]
    XRightWheel;                % [m]
    YRightWheel;                % [m]

  end
  %
  % Public methods
  methods
    function obj = TruckAbove()
      obj.createGeometry();
    end
    function setStates(obj, x, y, angleTruck, angleWheels)
    % Call this to change the angles.
        obj.XAnchor           = x;
        obj.YAnchor           = y;
        obj.AngleTruck        = angleTruck;
        obj.AngleWheels       = angleWheels;
        
        obj.addTracePoints();
        obj.updateTransforms();
    end
    function r = isAlive(obj)
    % Call this to check whether the figure window is still alive.
      r = isvalid(obj) && isvalid(obj.Truck);
    end
    function clearPoints(obj)
    % Call this to reset the traces.
      obj.Trace.clearpoints();
    end
  end
  %
  % Private methods
  methods (Access=private)
    function createGeometry(obj)

        % Load the points from file
        objectsTruck        = loadsvg(obj.FilenameTruck,0.01,false);
        objectsLeftWheel    = loadsvg(obj.FilenameLeftWheel,0.01,false);
        objectsRightWheel   = loadsvg(obj.FilenameRightWheel,0.01,false);
        objectsAnchor       = loadsvg(obj.FilenameAnchor,0.01,false);
        
        % Find Anchor coordinates (used to center everything)
        points = objectsAnchor{1};
        obj.XAnchorPixels = mean(points(:,1));
        obj.YAnchorPixels = mean(points(:,2));         

        % Create trace
        obj.Trace = animatedline(0,0, 'Color', 'r', 'linewidth', 4);
        
        % Initialize car
        obj.Truck        = hgtransform();
        obj.Wheels(1)    = hgtransform();
        obj.Wheels(2)    = hgtransform();

        tol = 1e-2; % Tolerance for reducing number of points in plot

        % Draw wheels
        for i = 1:length(objectsLeftWheel)
            points = objectsLeftWheel{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XLeftWheel = mean(points(:,1))-obj.XAnchorPixels;
            obj.YLeftWheel = mean(points(:,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Wheels(1),'edgecolor','k');
        end
        
        for i = 1:length(objectsRightWheel)
            points = objectsRightWheel{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XRightWheel = mean(points(:,1))-obj.XAnchorPixels;
            obj.YRightWheel = mean(points(:,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Wheels(2),'edgecolor','k');
        end

        % Draw the body
        for i = 1:length(objectsTruck)
            points = objectsTruck{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points, tol);
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Truck,'edgecolor','k');

            obj.XPixelMax = max(obj.XPixelMax, max(points(:,1)));
            obj.XPixelMin = min(obj.XPixelMin, min(points(:,1)));
        end
        obj.SVGScalingFactor = obj.TruckLength/(obj.XPixelMax-obj.XPixelMin);

        obj.XLeftWheel  = obj.XLeftWheel*obj.SVGScalingFactor;
        obj.YLeftWheel  = obj.YLeftWheel*obj.SVGScalingFactor;
        obj.XRightWheel = obj.XRightWheel*obj.SVGScalingFactor;
        obj.YRightWheel = obj.YRightWheel*obj.SVGScalingFactor;

        % Draw the trailer
        for i = 1:length(objectsTruck)
            points = objectsTruck{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points, tol);
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Truck,'edgecolor','k');
        end
    end

    function addTracePoints(obj)
        obj.Trace.addpoints(obj.XAnchor,obj.YAnchor);
    end

    function updateTransforms(obj)
        % Updates the transform matrices.
        obj.Truck.Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTruck, ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );
        
        obj.Wheels(1).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTruck, ...
            'translate',[obj.XLeftWheel,obj.YLeftWheel,0],...
            'zrotate',2*obj.AngleWheels,...
            'translate',[-obj.XLeftWheel,-obj.YLeftWheel,0],....
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );

        obj.Wheels(2).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTruck, ...
            'translate',[obj.XRightWheel,obj.YRightWheel,0],...
            'zrotate',2*obj.AngleWheels,...
            'translate',[-obj.XRightWheel,-obj.YRightWheel,0], ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );
    end
  end
end