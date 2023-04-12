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
    return ApiState.fromJson(stateJson);
}

const fetchWithTimeout = async (url: string, opts = {}, timeout = 5000) => {
    // Create a signal with timeout
    const signal = AbortSignal.timeout(timeout);

    // Make the fetch request
    const _fetchPromise = fetch(url, {
        ...opts,
        signal,
    });

    // Await the fetch with a catch in case it's aborted which signals an error
    return await _fetchPromise;
};

const doBasicRequest = async (url: string) => {
    let success = true;
    let data: any = "";
    try {
        const response = await fetchWithTimeout("http://trafficlightcontroller.iot.tacomano.micatechnologies.com:81" + url, {mode: 'cors'}, 1000);
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
        const response = await fetchWithTimeout("http://trafficlightcontroller.iot.tacomano.micatechnologies.com:81" + url, {mode: 'cors'}, 1000);
        const text = await response.text();
        result = JSON.parse(text);
    } catch (error) {
        console.log("Error fulfilling '" + url + "' request: " + error);
        result = "";
    }
    return result;
}