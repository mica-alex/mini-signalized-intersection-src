import React, {CSSProperties} from 'react';
import {IStackTokens, Stack} from "@fluentui/react";

export const trafficSignalBodyStyles: CSSProperties = {
    width: '60px',
    fontSize: '20px',
    margin: '10px',
    padding: '5px',
};
export const trafficSignalBodyStackTokens: IStackTokens = {childrenGap: 5};

export interface TrafficSignalBodyProps {
    color?: string;
    children?: React.ReactNode;
}

export const TrafficSignalBody = ({color, children}: TrafficSignalBodyProps) => {
    return (
        <Stack style={{backgroundColor: color ?? "black", ...trafficSignalBodyStyles}}
               tokens={trafficSignalBodyStackTokens}>
            {children}
        </Stack>
    );
};

export default TrafficSignalBody;

