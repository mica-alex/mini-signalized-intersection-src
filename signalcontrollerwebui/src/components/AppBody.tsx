import React from 'react';
import {bodyStackTokens, bodyStyles} from "../styles/GlobalStyles";
import {Stack} from "@fluentui/react";


interface AppBodyProps {
    children?: React.ReactNode;
}

export const AppBody = ({children}: AppBodyProps) => {
    return (
        <Stack.Item style={bodyStyles}>
            <Stack horizontal wrap tokens={bodyStackTokens} horizontalAlign="center">
                {children}
            </Stack>
        </Stack.Item>
    );
};

export default AppBody;