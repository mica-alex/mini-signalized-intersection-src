import React from 'react';
import {boldStyle, footerStackTokens, footerStyles} from "../styles/GlobalStyles";
import {Stack, Text, Theme, Toggle} from "@fluentui/react";
import {AzureThemeDark, AzureThemeLight} from "@fluentui/azure-themes";

interface AppFooterProps {
    theme: Theme | (() => Theme),
    setTheme: React.Dispatch<React.SetStateAction<Theme>>
}

export const AppFooter = ({theme, setTheme}: AppFooterProps) => {
    return (
        <Stack.Item style={footerStyles}>
            <Stack tokens={footerStackTokens} horizontalAlign="center">
                <Stack.Item>
                    <Text variant="large" styles={boldStyle}>
                        Theme
                    </Text>
                </Stack.Item>
                <Stack.Item>
                    <Toggle
                        onText="Dark"
                        offText="Light"
                        checked={theme === AzureThemeDark}
                        onChange={(ev, checked) => {
                            setTheme(checked ? AzureThemeDark : AzureThemeLight);
                        }}
                    />
                </Stack.Item>
                <Stack.Item>
                    <Text variant="xSmall">
                        &copy; {new Date().getFullYear()} Mica Technologies
                    </Text>
                </Stack.Item>
            </Stack>
        </Stack.Item>
    );
}

export default AppFooter;