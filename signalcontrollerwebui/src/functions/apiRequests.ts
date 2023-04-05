import {ApiState} from "./ApiState";

export const requestWalk = async () => {
    return doBasicRequest('/requestWalk');
}

export const disablePed = async () => {
    return doBasicRequest('/disablePed');
}

export const enablePed = async () => {
    return doBasicRequest('/enablePed');
}

export const disableBeacon = async () => {
    return doBasicRequest('/disableBeacon');
}

export const enableBeacon = async () => {
    return doBasicRequest('/enableBeacon');
}

export const disableFlash = async () => {
    return doBasicRequest('/disableFlash');
}

export const enableFlash = async () => {
    return doBasicRequest('/enableFlash');
}

export const disableForcedOffMode = async () => {
    return doBasicRequest('/disableForcedOffMode');
}

export const enableForcedOffMode = async () => {
    return doBasicRequest('/enableForcedOffMode');
}

export const disableForcedRedMode = async () => {
    return doBasicRequest('/disableForcedRedMode');
}

export const enableForcedRedMode = async () => {
    return doBasicRequest('/enableForcedRedMode');
}

export const disableForcedYellowMode = async () => {
    return doBasicRequest('/disableForcedYellowMode');
}

export const enableForcedYellowMode = async () => {
    return doBasicRequest('/enableForcedYellowMode');
}

export const disableForcedGreenMode = async () => {
    return doBasicRequest('/disableForcedGreenMode');
}

export const enableForcedGreenMode = async () => {
    return doBasicRequest('/enableForcedGreenMode');
}
export const getState = async () => {
    let stateJson = await doAdvancedRequest('/getState');
    let state = ApiState.fromJson(stateJson);
    return state;
}


const doBasicRequest = async (url: string) => {
    let success = true;
    let data: any = "";
    try {
        const response = await fetch("http://trafficlightcontroller.iot.tacomano.micatechnologies.com:81" + url, {mode: 'cors'});
        //const response = await fetch("http://"+window.location.host+":81"+url,{mode: 'cors'});
        data = JSON.parse(await response.text());
        if (data.success) {
            console.log("Request successful!");
        } else {
            console.log("Failure executing '" + url + "' request: " + data);
            success = false;
        }
    } catch (error) {
        console.log("Error fulfilling '" + url + "' request: " + error);
        success = false;
    }
    return success;
}

const doAdvancedRequest = async (url: string) => {
    let result = "";
    try {
        const response = await fetch("http://trafficlightcontroller.iot.tacomano.micatechnologies.com:81" + url, {mode: 'cors'});
        //const response = await fetch("http://"+window.location.host+":81"+url,{mode: 'cors'});
        const text = await response.text();
        result = JSON.parse(text);
    } catch (error) {
        console.log("Error fulfilling '" + url + "' request: " + error);
        result = "";
    }
    return result;
}