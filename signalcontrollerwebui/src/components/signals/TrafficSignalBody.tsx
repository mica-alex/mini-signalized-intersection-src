import React, {CSSProperties} from 'react';
import {IStackTokens, Stack} from "@fluentui/react";

export const trafficSignalBodyStyles: CSSProperties = {
    width: '60px',
    fontSize: '20px',
    margin: '10px',
    padding: '5px',
};

export const trafficSignalBodySmallStyles: CSSProperties = {
    width: '50px',
    fontSize: '20px',
    margin: '10px',
    padding: '5px',
};
export const trafficSignalBodyStackTokens: IStackTokens = {childrenGap: 5};

export interface TrafficSignalBodyProps {
    color?: string;
    small?: boolean;
    children?: React.ReactNode;
}

export const TrafficSignalBody = ({color, small, children}: TrafficSignalBodyProps) => {
    let desiredStyles = small ? trafficSignalBodySmallStyles : trafficSignalBodyStyles;
    return (
        <Stack style={{backgroundColor: color ?? "black", ...desiredStyles}}
               tokens={trafficSignalBodyStackTokens}>
            {children}
        </Stack>
    );
};

export default TrafficSignalBody;

