classdef SemiTruck < handle
  properties (SetAccess=private)    
    FilenameTractor = 'semiTruck_tractor.svg';
    FilenameTractorLeftWheel = 'semiTruck_tractor_left_wheel.svg';
    FilenameTractorRightWheel = 'semiTruck_tractor_right_wheel.svg';
    FilenameTrailer = 'semiTruck_trailer.svg';
    FilenameAnchor = 'semiTruck_anchor.svg';

    SVGScalingFactor;
    XPixelMax = 0;
    XPixelMin = inf;

    TractorLength = 4;          % [m]

    XAnchorPixels = 0;      % [pixels]
    YAnchorPixels = 0;      % [pixels]

    XAnchor = 0;            % [m]
    YAnchor = 0;            % [m]

    AngleTractor = 0;       % [rad]
    AngleTrailer = 0;       % [rad]
    AngleWheels  = 0;       % [rad]

    Tractor         = gobjects(1);
    TractorWheels   = gobjects(2);
    Trailer         = gobjects(1);
    Trace           = gobjects(1);

    XLeftWheel;             % [m]
    YLeftWheel;             % [m]
    XRightWheel;            % [m]
    YRightWheel;            % [m]

  end
  %
  % Public methods
  methods
    function obj = SemiTruck()
      obj.createGeometry();
    end
    function setStates(obj, x, y, angleTractor, angleTrailer, angleWheels)
    % Call this to change the angles.
        obj.XAnchor           = x;
        obj.YAnchor           = y;
        obj.AngleTractor      = angleTractor;
        obj.AngleTrailer      = angleTrailer;
        obj.AngleWheels       = angleWheels;
        
        obj.addTracePoints();
        obj.updateTransforms();
    end
    function r = isAlive(obj)
    % Call this to check whether the figure window is still alive.
      r = isvalid(obj) && isvalid(obj.Tractor);
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
        objectsTractor              = loadsvg(obj.FilenameTractor,0.01,false);
        objectsTrailer              = loadsvg(obj.FilenameTrailer,0.01,false);
        objectsLeftTractorWheel     = loadsvg(obj.FilenameTractorLeftWheel,0.01,false);
        objectsRightTractorWheel    = loadsvg(obj.FilenameTractorRightWheel,0.01,false);
        objectsAnchor               = loadsvg(obj.FilenameAnchor,0.01,false);
        
        % Find Anchor coordinates (used to center everything)
        points = objectsAnchor{1};
        obj.XAnchorPixels = mean(points(:,1));
        obj.YAnchorPixels = mean(points(:,2));

        % Create trace
        obj.Trace = animatedline(0,0, 'Color', 'r', 'linewidth', 4);
        
        % Initialize car
        obj.Tractor             = hgtransform();
        obj.Trailer             = hgtransform();
        obj.TractorWheels(1)    = hgtransform();
        obj.TractorWheels(2)    = hgtransform();

        tol = 1e-2; % Tolerance for reducing number of points in plot

        % Draw wheels
        for i = 1:length(objectsLeftTractorWheel)
            points = objectsLeftTractorWheel{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XLeftWheel = mean(points(:,1))-obj.XAnchorPixels;
            obj.YLeftWheel = mean(points(:,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.TractorWheels(1),'edgecolor','k');
        end
        
        for i = 1:length(objectsRightTractorWheel)
            points = objectsRightTractorWheel{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XRightWheel = mean(points(:,1))-obj.XAnchorPixels;
            obj.YRightWheel = mean(points(:,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.TractorWheels(2),'edgecolor','k');
        end

        % Draw the body
        for i = 1:length(objectsTractor)
            points = objectsTractor{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points, tol);
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Tractor,'edgecolor','k');

            obj.XPixelMax = max(obj.XPixelMax, max(points(:,1)));
            obj.XPixelMin = min(obj.XPixelMin, min(points(:,1)));
        end
        obj.SVGScalingFactor = obj.TractorLength/(obj.XPixelMax-obj.XPixelMin);

        obj.XLeftWheel = obj.XLeftWheel*obj.SVGScalingFactor;
        obj.YLeftWheel = obj.YLeftWheel*obj.SVGScalingFactor;
        obj.XRightWheel = obj.XRightWheel*obj.SVGScalingFactor;
        obj.YRightWheel = obj.YRightWheel*obj.SVGScalingFactor;

        % Draw the trailer
        for i = 1:length(objectsTrailer)
            points = objectsTrailer{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points, tol);
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Trailer,'edgecolor','k');
        end
    end

    function addTracePoints(obj)
        obj.Trace.addpoints(obj.XAnchor,obj.YAnchor);
    end

    function updateTransforms(obj)
        % Updates the transform matrices.
        obj.Tractor.Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTractor, ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );

        obj.Trailer.Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTractor-obj.AngleTrailer, ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );
        
        obj.TractorWheels(1).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTractor, ...
            'translate',[obj.XLeftWheel,obj.YLeftWheel,0],...
            'zrotate',2*obj.AngleWheels,...
            'translate',[-obj.XLeftWheel,-obj.YLeftWheel,0],....
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );

        obj.TractorWheels(2).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.AngleTractor, ...
            'translate',[obj.XRightWheel,obj.YRightWheel,0],...
            'zrotate',2*obj.AngleWheels,...
            'translate',[-obj.XRightWheel,-obj.YRightWheel,0], ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );
    end
  end
end