function semiTruckSFunction(block)
    setup(block)
end

function setup(block)
    block.NumInputPorts = 5;
    block.NumOutputPorts = 0;

    block.SetPreCompInpPortInfoToDynamic;
    block.InputPort(1).Dimensions = 1;
    block.InputPort(2).Dimensions = 1;
    block.InputPort(3).Dimensions = 1;
    block.InputPort(4).Dimensions = 1;
    block.InputPort(5).Dimensions = 1;

    block.RegBlockMethod('Start', @start);
    block.RegBlockMethod('Outputs', @output);
    block.SetSimViewingDevice(true);
end

function start(block)
    % Figure setup
    close all;
    figure('position',[100,100,1500,500]);
    grid on; hold on; daspect([1,1,1])
    xlim([-20, 50]);
    ylim([-6, 6]);

    % Setting up visualization objects
    ud = get_param(block.BlockHandle, 'UserData');
    if isempty(ud)
        visRoad = [];
        visSemiTruck = [];
    else
        visRoad = ud.visRoad;
        visSemiTruck = ud.visSemiTruck;
    end
    if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visSemiTruck) || ~isa(visSemiTruck, 'SemiTruck') || ~visSemiTruck.isAlive
        visRoad = RoadAbove();
        visSemiTruck = SemiTruck();
    end
    visSemiTruck.clearPoints();
    
    ud.visRoad = visRoad;
    ud.visSemiTruck = visSemiTruck;
    set_param(block.BlockHandle, 'UserData', ud);
end

function output(block)
    if block.IsMajorTimeStep
        ud = get_param(block.BlockHandle, 'UserData');
        
        visRoad = ud.visRoad;
        visSemiTruck = ud.visSemiTruck;
        if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visSemiTruck) || ~isa(visSemiTruck, 'SemiTruck') || ~visSemiTruck.isAlive
            return;
        end

        visRoad.setStates(block.InputPort(1).Data);
        visSemiTruck.setStates(block.InputPort(1).Data, block.InputPort(2).Data, block.InputPort(3).Data, block.InputPort(4).Data, block.InputPort(5).Data);

        xlim(block.InputPort(1).Data+[-20, 50]);
        ylim(block.InputPort(2).Data+[-6, 6]);    

        drawnow;
    end
end
