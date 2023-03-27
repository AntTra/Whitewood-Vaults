classdef TruckSide < handle
  properties (SetAccess=private)    
    FilenameTruck = 'truckSide.svg';
    FilenameLeftHubcap = 'truckSide_left_hubcap.svg';
    FilenameRightHubcap = 'truckSide_right_hubcap.svg';
    FilenameAnchor = 'truckSide_anchor.svg';

    SVGScalingFactor;
    XPixelMax = 0;
    XPixelMin = inf;
    XLim = [-20, 50];
    YLim = [-10, 10];

    FigurePosition = [100,100,1500,500];

    TruckLength = 8;        % [m]
    
    XAnchorPixels = 0;      % [pixels]
    YAnchorPixels = 0;      % [pixels]

    XAnchor = 0;            % [m]
    YAnchor = 0;            % [m]

    Angle = 0;              % [rad]

    Truck = gobjects(1);
    Hubcaps = gobjects(2);
    Trace = gobjects(1);
    Speedometer = gobjects(1);

    XLeftHubcap  = 0;             % [m]
    YLeftHubcap  = 0;             % [m]
    XRightHubcap = 0;             % [m]
    YRightHubcap = 0;             % [m]

    Speed = 0;

    IsRoadFlat = 0;
  end
  %
  % Public methods
  methods
    function obj = TruckSide()
      obj.createGeometry();
      %obj.updateTransforms();
    end
    function setStates(obj, x, y, angle, speed, isRoadFlat)
        % Call this to change the angles.
        obj.IsRoadFlat = isRoadFlat;
        
        if isRoadFlat > 0.5
            obj.Angle   = 0;
            obj.YAnchor = 0;
        else
            obj.Angle   = angle;
            obj.YAnchor = y;
        end
 
        obj.XAnchor = x;
        obj.Speed   = speed;
 
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
        objectsTruck = loadsvg(obj.FilenameTruck,0.01,false);
        objectsLeftHubcap   = loadsvg(obj.FilenameLeftHubcap,0.01,false);
        objectsRightHubcap  = loadsvg(obj.FilenameRightHubcap,0.01,false);
        objectsAnchor       = loadsvg(obj.FilenameAnchor,0.01,false);

        % Find Anchor coordinates (used to center everything)
        points = objectsAnchor{1};
        obj.XAnchorPixels = mean(points(:,1));
        obj.YAnchorPixels = mean(points(:,2));

        % Define figure to plot in
        fig = figure('position',obj.FigurePosition);
        ax = axes('Parent',fig); hold on;

        % Draw road
        x = linspace(min(obj.XLim)-1,max(obj.XLim)+1,100);
        if obj.IsRoadFlat > 0.5
            y = 0*x;
        else
            [y,~] = truckRoad(x);
        end
        obj.Trace = animatedline(x,y, 'color', [0.5,0.5,0.5], 'linewidth', 3);

        % Initialize car
        obj.Truck           = hgtransform();
        obj.Hubcaps(1)      = hgtransform();
        obj.Hubcaps(2)      = hgtransform();

        tol = 1e-3; % Tolerance for reducing number of points in plot

        % Draw hubcaps
        for i = 1:length(objectsLeftHubcap)
            points = objectsLeftHubcap{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XLeftHubcap = mean(points(1,1))-obj.XAnchorPixels;
            obj.YLeftHubcap = mean(points(1,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Hubcaps(1),'edgecolor','k');
        end
        
        for i = 1:length(objectsRightHubcap)
            points = objectsRightHubcap{i};
            if any(isnan(points)) % Quick hack for poor drawings
                continue 
            end 
            points = reducepoly(points,tol);
            obj.XRightHubcap = mean(points(1,1))-obj.XAnchorPixels;
            obj.YRightHubcap = mean(points(1,2))-obj.YAnchorPixels;
            patch(points(:,1),points(:,2), 'w', 'Parent',obj.Hubcaps(2),'edgecolor','k');
        end

        % Draw the truck
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

        obj.XLeftHubcap = obj.XLeftHubcap*obj.SVGScalingFactor;
        obj.YLeftHubcap = obj.YLeftHubcap*obj.SVGScalingFactor;
        obj.XRightHubcap = obj.XRightHubcap*obj.SVGScalingFactor;
        obj.YRightHubcap = obj.YRightHubcap*obj.SVGScalingFactor;

        % Draw Speedometer
        obj.Speedometer = text(obj.XAnchor-0.4,obj.YAnchor+2.4,0,sprintf('%.2f m/s', obj.Speed));

        % Initialize the axes.
        ax.DataAspectRatio = [1 1 1];
        grid(ax,'on');
        ax.SortMethod = 'childorder';
    end

    function addTracePoints(obj)
        x = linspace(obj.XAnchor+obj.XLim(1)-1,obj.XAnchor+obj.XLim(2)+1,100);

        if obj.IsRoadFlat > 0.5
            y = 0*x;
        else
            [y,~] = truckRoad(x);
        end
        clearpoints(obj.Trace);
        obj.Trace.addpoints(x,y);
    end

    function updateTransforms(obj)
        % Updates the transform matrices.
        obj.Truck.Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.Angle, ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );

        obj.Hubcaps(1).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.Angle, ...
            'translate',[obj.XLeftHubcap,obj.YLeftHubcap,0],...
            'zrotate',-obj.XAnchor,...
            'translate',[-obj.XLeftHubcap,-obj.YLeftHubcap,0], ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );

        obj.Hubcaps(2).Matrix = makehgtform( ...
            'translate',[obj.XAnchor,obj.YAnchor,0], ...
            'zrotate',obj.Angle, ...
            'translate',[obj.XRightHubcap,obj.YRightHubcap,0],...
            'zrotate',-obj.XAnchor,...
            'translate',[-obj.XRightHubcap,-obj.YRightHubcap,0], ...
            'scale',obj.SVGScalingFactor, ...
            'translate',[-obj.XAnchorPixels,-obj.YAnchorPixels,0] ...
            );
        
        obj.Speedometer.String = sprintf('%.2f m/s', obj.Speed);
        dx = -0.4*cos(obj.Angle) - 2.4*sin(obj.Angle);
        dy = -0.4*sin(obj.Angle) + 2.4*cos(obj.Angle);
        obj.Speedometer.Position = [obj.XAnchor+dx,obj.YAnchor+dy,0];
        obj.Speedometer.Rotation = rad2deg(obj.Angle);

        xlim(obj.XAnchor+obj.XLim)
        ylim(obj.YAnchor+obj.YLim)
        drawnow;
    end
  end
end