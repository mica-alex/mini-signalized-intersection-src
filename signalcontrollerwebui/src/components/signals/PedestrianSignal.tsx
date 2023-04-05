import React, {CSSProperties} from 'react';
import {IStackTokens, Stack} from "@fluentui/react";

export const pedestrianSignalStyles: CSSProperties = {
    width: '73px',
    fontSize: '20px',
    margin: '10px',
    padding: '10px',
    borderRadius: '10px',
};
export const pedestrianSignalStackTokens: IStackTokens = {childrenGap: 5};

export interface PedestrianSignalProps {
    color?: string;
    walk: boolean;
    dontWalk: boolean;
}

export const PedestrianSignal = ({color, walk, dontWalk}: PedestrianSignalProps) => {
    let unpoweredColor = '#111';
    return (
        <Stack horizontal style={{backgroundColor: color ?? "black", ...pedestrianSignalStyles}}
               tokens={pedestrianSignalStackTokens}>
            <Stack.Item>
                <svg fill={walk ? "white" : unpoweredColor} viewBox="17.642 5.022 24.187 40.494" width="24.187"
                     height="40.494">
                    <path
                        d="M 35.337 19.105 C 35.437 18.132 33.572 11.048 31.175 10.81 C 30.838 10.722 30.48 10.765 30.174 10.932 L 19.747 15.188 L 19.064 24.965 L 21.037 24.965 L 22.757 16.88 L 24.989 16.498 C 24.989 16.498 23.398 21.034 23.169 23.288 C 23.147 24.3 23.275 25.31 23.55 26.284 L 17.53 43.227 L 20.028 45.516 L 27.034 30.841 L 29.727 34.218 L 32.463 45.401 L 35.869 44.393 L 33.63 32.267 L 30.167 24.57 L 32.327 20.09 L 33.723 22.734 L 40.204 25.736 L 41.717 24.224 L 35.337 19.105 Z M 34.097 5.042 C 32.556 4.857 31.169 5.992 31.045 7.542 C 30.86 9.083 31.995 10.469 33.544 10.594 C 35.68 10.81 37.25 8.631 36.369 6.672 C 35.96 5.764 35.097 5.143 34.106 5.042"
                        transform="matrix(1, 0, 0, 1, 0.111778, 0)"></path>
                </svg>
            </Stack.Item>
            <Stack.Item>
                <svg fill={dontWalk ? "orange" : unpoweredColor} viewBox="5.625 3.561 26.262 40.496" width="26.262"
                     height="40.496">
                    <path
                        d="M 7.641 44.052 C 8.016 43.597 8.442 43.104 8.486 42.303 L 8.486 36.444 C 8.486 33.893 7.625 33.46 6.786 32.678 C 5.397 31.387 5.606 29.557 5.683 27.194 C 5.896 20.642 6.143 16.695 6.168 10.574 C 6.171 9.794 6.804 9.157 7.585 9.157 C 8.366 9.157 9.002 9.794 9.002 10.574 L 9.488 20.508 L 10.132 20.492 C 10.234 15.955 10.442 11.377 10.442 6.842 C 10.442 6.063 11.078 5.426 11.859 5.426 C 12.638 5.426 13.274 6.063 13.274 6.842 C 13.274 6.855 13.274 6.87 13.279 6.883 L 13.474 20.505 L 14.13 20.505 C 14.314 15.365 14.681 10.111 14.681 4.977 C 14.681 4.197 15.318 3.561 16.096 3.561 C 16.877 3.561 17.514 4.197 17.514 4.977 L 17.514 4.995 L 17.819 20.505 L 18.678 20.505 C 18.727 15.926 18.779 11.347 18.829 6.768 C 18.861 6.018 19.491 5.426 20.243 5.426 C 21.007 5.426 21.644 6.04 21.66 6.809 L 22.36 25.075 C 22.354 25.413 22.656 25.665 22.993 25.665 C 23.185 25.665 23.621 25.528 23.96 25.009 L 27.162 20.371 C 28.374 18.669 29.991 18.333 31.887 19.05 C 30.712 21.259 28.287 26.706 25.827 29.766 C 24.53 31.794 20.179 33.828 20.179 36.438 L 20.179 41.78 C 20.179 42.879 21.263 44.121 21.215 44.054 L 7.641 44.052 Z"></path>
                </svg>
            </Stack.Item>
        </Stack>
    );
};

export default PedestrianSignal;