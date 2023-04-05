import React from 'react';
import {Stack, Text} from "@fluentui/react";
import {
    bodySectionBodyStyles,
    bodySectionContentStackTokens,
    bodySectionHeaderStyles,
    bodySectionStackTokens,
    bodySectionStyles,
    bodySectionWideStyles,
    boldStyle
} from "../../styles/GlobalStyles";

interface BodySectionProps {
    title: string;
    wide?: boolean;
    horizontal?: boolean;
    children?: React.ReactNode;
}

export const BodySection = ({title, wide, horizontal, children}: BodySectionProps) => {
    return (
        <Stack.Item>
            <Stack tokens={bodySectionStackTokens} style={wide ? bodySectionWideStyles : bodySectionStyles}>
                <Stack.Item style={bodySectionHeaderStyles}>
                    <Text variant="large" styles={boldStyle}>
                        {title}
                    </Text>
                </Stack.Item>
                <Stack.Item style={bodySectionBodyStyles}>
                    <Stack tokens={bodySectionContentStackTokens} verticalAlign={"center"} horizontalAlign={"center"}
                           horizontal={horizontal}>
                        {children}
                    </Stack>
                </Stack.Item>
            </Stack>
        </Stack.Item>
    );
};

export default BodySection;