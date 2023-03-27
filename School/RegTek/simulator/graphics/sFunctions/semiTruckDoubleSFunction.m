function semiTruckDoubleSFunction(block)
    setup(block)
end

function setup(block)
    block.NumInputPorts = 10;
    block.NumOutputPorts = 0;

    block.SetPreCompInpPortInfoToDynamic;
    block.InputPort(1).Dimensions = 1;
    block.InputPort(2).Dimensions = 1;
    block.InputPort(3).Dimensions = 1;
    block.InputPort(4).Dimensions = 1;
    block.InputPort(5).Dimensions = 1;

    block.InputPort(6).Dimensions = 1;
    block.InputPort(7).Dimensions = 1;
    block.InputPort(8).Dimensions = 1;
    block.InputPort(9).Dimensions = 1;
    block.InputPort(10).Dimensions = 1;

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
        visSemiTruckOne = [];
        visSemiTruckTwo = [];
    else
        visRoad = ud.visRoad;
        visSemiTruckOne = ud.visSemiTruckOne;
        visSemiTruckTwo = ud.visSemiTruckTwo;
    end
    if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visSemiTruckOne) || ~isa(visSemiTruckOne, 'SemiTruck') || ~visSemiTruckOne.isAlive
        visRoad = RoadAbove();
        visSemiTruckOne = SemiTruck();
        visSemiTruckTwo = SemiTruck();
    end
    visSemiTruckOne.clearPoints();
    visSemiTruckTwo.clearPoints();
    
    ud.visRoad = visRoad;
    ud.visSemiTruckOne = visSemiTruckOne;
    ud.visSemiTruckTwo = visSemiTruckTwo;
    set_param(block.BlockHandle, 'UserData', ud);
end

function output(block)
    if block.IsMajorTimeStep
        ud = get_param(block.BlockHandle, 'UserData');
        
        visRoad = ud.visRoad;
        visSemiTruckOne = ud.visSemiTruckOne;
        visSemiTruckTwo = ud.visSemiTruckTwo;
        if isempty(visRoad) || ~isa(visRoad, 'RoadAbove') || ~visRoad.isAlive || isempty(visSemiTruckOne) || ~isa(visSemiTruckOne, 'SemiTruck') || ~visSemiTruckOne.isAlive
            return;
        end

        visRoad.setStates(block.InputPort(1).Data);
        visSemiTruckOne.setStates(block.InputPort(1).Data, block.InputPort(2).Data, block.InputPort(3).Data, block.InputPort(4).Data, block.InputPort(5).Data);
        visSemiTruckTwo.setStates(block.InputPort(6).Data, block.InputPort(7).Data, block.InputPort(8).Data, block.InputPort(9).Data, block.InputPort(10).Data);

        xlim(block.InputPort(1).Data+[-20, 50]);
        ylim(block.InputPort(2).Data+[-6, 6]);    

        drawnow;
    end
end
