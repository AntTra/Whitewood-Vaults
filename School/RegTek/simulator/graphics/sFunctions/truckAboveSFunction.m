function truckAboveSFunction(block)
    setup(block)
end

function setup(block)
    block.NumInputPorts = 4;
    block.NumOutputPorts = 0;

    block.SetPreCompInpPortInfoToDynamic;
    block.InputPort(1).Dimensions = 1;
    block.InputPort(2).Dimensions = 1;
    block.InputPort(3).Dimensions = 1;
    block.InputPort(4).Dimensions = 1;

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
        visTruck = [];
    else
        visRoad = ud.visRoad;
        visTruck = ud.visTruck;
    end
    if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visTruck) || ~isa(visTruck, 'TruckAbove') || ~visTruck.isAlive
        visRoad = RoadAbove();
        visTruck = TruckAbove();
    end
    visTruck.clearPoints();
    
    ud.visRoad = visRoad;
    ud.visTruck = visTruck;
    set_param(block.BlockHandle, 'UserData', ud);
end

function output(block)
    if block.IsMajorTimeStep
        ud = get_param(block.BlockHandle, 'UserData');
        
        visRoad = ud.visRoad;
        visTruck = ud.visTruck;
        if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visTruck) || ~isa(visTruck, 'TruckAbove') || ~visTruck.isAlive
            return;
        end

        visRoad.setStates(block.InputPort(1).Data);
        visTruck.setStates(block.InputPort(1).Data, block.InputPort(2).Data, block.InputPort(3).Data, block.InputPort(4).Data);

        xlim(block.InputPort(1).Data+[-20, 50]);
        ylim(block.InputPort(2).Data+[-6, 6]);    

        drawnow;
    end
end
