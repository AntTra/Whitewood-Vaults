function truckSideSFunction(block)
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
    close all;
    ud = get_param(block.BlockHandle, 'UserData');
    if isempty(ud)
        vis = [];
    else
        vis = ud.vis;
    end
    if isempty(vis) || ~isa(vis, 'TruckSide') || ~vis.isAlive
        vis = TruckSide();
    end
    ud.vis = vis;
    set_param(block.BlockHandle, 'UserData', ud);
end

function output(block)
    if block.IsMajorTimeStep
        ud = get_param(block.BlockHandle, 'UserData');
        vis = ud.vis;
        if isempty(vis) || ~isa(vis, 'TruckSide') || ~vis.isAlive
            return;
        end
        vis.setStates(block.InputPort(1).Data, block.InputPort(2).Data, block.InputPort(3).Data, block.InputPort(4).Data, block.InputPort(5).Data);
    end
end
