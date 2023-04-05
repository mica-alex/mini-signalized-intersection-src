import React, {CSSProperties} from 'react';
import {Stack} from "@fluentui/react";

export const trafficSignalBulbStyles: CSSProperties = {
    height: '50px',
    width: '50px',
    borderRadius: '50%',
    fontSize: '50px',
    margin: '0',
    padding: '0',
};

export interface TrafficSignalBulbProps {
    color: string;
    powered: boolean;
    leftArrow?: boolean;
    rightArrow?: boolean;
    thruArrow?: boolean;
}

export const TrafficSignalBulb = ({color, powered, leftArrow, rightArrow, thruArrow}: TrafficSignalBulbProps) => {
    let unpoweredColor = '#111';
    let lessUnpoweredColor = '#222';
    if (leftArrow || rightArrow || thruArrow) {
        return (
            <Stack.Item>
                <Stack style={{...trafficSignalBulbStyles, backgroundColor: unpoweredColor}}
                       verticalAlign={"center"} horizontalAlign={"center"}>
                    {leftArrow &&
                        <svg fill={powered ? color : lessUnpoweredColor} viewBox="3.008 1.753 40 33.876" width="40"
                             height="33.876">
                            <g id="SVGRepo_iconCarrier"
                               transform="matrix(-1.284416, 0, 0, -1.284416, 43.007634, 38.690763)">
                                <g>
                                    <g id="c100_arrow">
                                        <path
                                            d="M0,15.571c0.001,1.702,1.383,3.081,3.085,3.083l17.528-0.002l-4.738,4.739c-1.283,1.284-1.349,3.301-0.145,4.507 c1.205,1.201,3.222,1.138,4.507-0.146l9.896-9.898c1.287-1.283,1.352-3.301,0.146-4.506c-0.033-0.029-0.068-0.051-0.1-0.08 c-0.041-0.043-0.07-0.094-0.113-0.139l-9.764-9.762c-1.268-1.266-3.27-1.316-4.474-0.111c-1.205,1.205-1.153,3.208,0.111,4.476 l4.755,4.754H3.085C1.381,12.485,0,13.865,0,15.571z"></path>
                                    </g>
                                    <g id="Capa_1_46_"></g>
                                </g>
                            </g>
                        </svg>}
                    {rightArrow &&
                        <svg fill={powered ? color : lessUnpoweredColor} viewBox="3.008 1.753 40 36.938" width="40"
                             height="36.938">
                            <g id="SVGRepo_bgCarrier" strokeWidth="0"
                               transform="matrix(1.284416, 0, 0, 1.284416, 3.007648, 1.752855)"></g>
                            <g id="SVGRepo_tracerCarrier" strokeLinecap="round" strokeLinejoin="round"
                               transform="matrix(1.284416, 0, 0, 1.284416, 3.007648, 1.752855)"></g>
                            <g id="SVGRepo_iconCarrier"
                               transform="matrix(1.284416, 0, 0, 1.284416, 3.007648, 1.752855)">
                                <g>
                                    <g id="c100_arrow">
                                        <path
                                            d="M0,15.571c0.001,1.702,1.383,3.081,3.085,3.083l17.528-0.002l-4.738,4.739c-1.283,1.284-1.349,3.301-0.145,4.507 c1.205,1.201,3.222,1.138,4.507-0.146l9.896-9.898c1.287-1.283,1.352-3.301,0.146-4.506c-0.033-0.029-0.068-0.051-0.1-0.08 c-0.041-0.043-0.07-0.094-0.113-0.139l-9.764-9.762c-1.268-1.266-3.27-1.316-4.474-0.111c-1.205,1.205-1.153,3.208,0.111,4.476 l4.755,4.754H3.085C1.381,12.485,0,13.865,0,15.571z"></path>
                                    </g>
                                    <g id="Capa_1_46_"></g>
                                </g>
                            </g>
                        </svg>}
                    {thruArrow &&
                        <svg fill={powered ? color : lessUnpoweredColor} viewBox="4.539 0.222 36.938 40" width="36.938"
                             height="40">
                            <g id="SVGRepo_bgCarrier" strokeWidth="0"
                               transform="matrix(0, -1.284416, 1.284416, 0, 4.53869, 40.221803)"></g>
                            <g id="SVGRepo_tracerCarrier" strokeLinecap="round" strokeLinejoin="round"
                               transform="matrix(0, -1.284416, 1.284416, 0, 4.53869, 40.221803)"></g>
                            <g id="SVGRepo_iconCarrier"
                               transform="matrix(0, -1.284416, 1.284416, 0, 4.53869, 40.221803)">
                                <g>
                                    <g id="c100_arrow">
                                        <path
                                            d="M0,15.571c0.001,1.702,1.383,3.081,3.085,3.083l17.528-0.002l-4.738,4.739c-1.283,1.284-1.349,3.301-0.145,4.507 c1.205,1.201,3.222,1.138,4.507-0.146l9.896-9.898c1.287-1.283,1.352-3.301,0.146-4.506c-0.033-0.029-0.068-0.051-0.1-0.08 c-0.041-0.043-0.07-0.094-0.113-0.139l-9.764-9.762c-1.268-1.266-3.27-1.316-4.474-0.111c-1.205,1.205-1.153,3.208,0.111,4.476 l4.755,4.754H3.085C1.381,12.485,0,13.865,0,15.571z"></path>
                                    </g>
                                    <g id="Capa_1_46_"></g>
                                </g>
                            </g>
                        </svg>}
                </Stack>
            </Stack.Item>
        );
    } else {
        return (
            <Stack.Item>
                <div style={{...trafficSignalBulbStyles, backgroundColor: powered ? color : unpoweredColor}}/>
            </Stack.Item>
        );
    }
};

export default TrafficSignalBulb;