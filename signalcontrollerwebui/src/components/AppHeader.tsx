import React from 'react';
import {boldStyle, headerInfoStackTokens, headerStackTokens, headerStyles, italicStyle} from "../styles/GlobalStyles";
import {Stack, Text} from "@fluentui/react";
import logo from "../logo.svg";

export const AppHeader = () => {
    return (
        <Stack.Item style={headerStyles}>
            <Stack horizontal verticalAlign={"center"} tokens={headerStackTokens}>
                <Stack.Item>
                    <img className="App-logo" src={logo} alt="logo" width={100} height={100}/>
                </Stack.Item>
                <Stack.Item>
                    <Stack tokens={headerInfoStackTokens}>
                        <Stack.Item>
                            <Text variant="xxLarge" styles={boldStyle}>
                                Traffic Light Controller
                            </Text>
                        </Stack.Item>
                        <Stack.Item>
                            <Text variant="xSmall" styles={italicStyle}>
                                Version: 1.0.0
                            </Text>
                        </Stack.Item>
                    </Stack>
                </Stack.Item>
            </Stack>
        </Stack.Item>
    );
}

export default AppHeader;