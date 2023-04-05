export class ApiState {
    public lamps: ApiStateLampState[] = [];
    public flashMode: boolean = false;
    public walkRequested: boolean = false;
    public pedEnabled: boolean = false;
    public statePhaseFlash: boolean = false;
    public stateForcedOffMode: boolean = false;
    public stateForcedRedMode: boolean = false;
    public stateForcedYellowMode: boolean = false;
    public stateForcedGreenMode: boolean = false;
    public statePhaseIndex: number = 0;
    public statePhaseMaxIndex: number = 6;
    public stateLastTime: number = 0;
    public stateIsBeaconEnabled: boolean = false;
    public lampPrimaryWalk: boolean = false;
    public lampPrimaryDontWalk: boolean = false;
    public lampSecondaryRed: boolean = false;
    public lampSecondaryYellow: boolean = false;
    public lampSecondaryGreen: boolean = false;
    public lampPrimaryRed: boolean = false;
    public lampPrimaryYellow: boolean = false;
    public lampPrimaryYellowArrow: boolean = false;
    public lampPrimaryGreenArrow: boolean = false;

    static fromJson(json: any): ApiState {
        const state = new ApiState();
        if (json.lamps) state.lamps = json.lamps;
        if (json.flashMode) state.flashMode = json.flashMode;
        if (json.stateForcedOffMode) state.stateForcedOffMode = json.stateForcedOffMode;
        if (json.stateForcedRedMode) state.stateForcedRedMode = json.stateForcedRedMode;
        if (json.stateForcedYellowMode) state.stateForcedYellowMode = json.stateForcedYellowMode;
        if (json.stateForcedGreenMode) state.stateForcedGreenMode = json.stateForcedGreenMode;
        if (json.walkRequested) state.walkRequested = json.walkRequested;
        if (json.pedEnabled) state.pedEnabled = json.pedEnabled;
        if (json.statePhaseFlash) state.statePhaseFlash = json.statePhaseFlash;
        if (json.statePhaseIndex) state.statePhaseIndex = json.statePhaseIndex;
        if (json.statePhaseMaxIndex) state.statePhaseMaxIndex = json.statePhaseMaxIndex;
        if (json.stateLastTime) state.stateLastTime = json.stateLastTime;
        if (json.stateIsBeaconEnabled) state.stateIsBeaconEnabled = json.stateIsBeaconEnabled;
        for (let i = 0; i < state.lamps.length; i++) {
            let lamp = state.lamps[i];
            if (lamp.slot === 1 && lamp.channel === 1) {
                state.lampPrimaryWalk = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 2) {
                state.lampPrimaryDontWalk = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 3) {
                state.lampSecondaryRed = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 4) {
                state.lampSecondaryYellow = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 5) {
                state.lampSecondaryGreen = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 6) {
                state.lampPrimaryRed = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 7) {
                state.lampPrimaryYellow = lamp.powered;
            }
            if (lamp.slot === 1 && lamp.channel === 8) {
                state.lampPrimaryYellowArrow = lamp.powered;
            }
            if (lamp.slot === 2 && lamp.channel === 1) {
                state.lampPrimaryGreenArrow = lamp.powered;
            }
        }
        return state;
    }
}

class ApiStateLampState {
    public slot: number = 0;
    public channel: number = 0;
    public powered: boolean = false;
}