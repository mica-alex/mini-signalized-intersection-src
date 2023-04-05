// eslint-disable-next-line @typescript-eslint/no-unused-vars
import React, {CSSProperties} from 'react';
import {FontWeights, getColorFromRGBA, IStackStyles, IStackTokens, ITextStyles} from "@fluentui/react";

export const boldStyle: Partial<ITextStyles> = {root: {fontWeight: FontWeights.semibold}};
export const italicStyle: Partial<ITextStyles> = {root: {fontStyle: 'italic'}};
export const rootStackTokens: IStackTokens = {childrenGap: 15};
export const rootStackStyles: Partial<IStackStyles> = {
    root: {
        margin: '0 auto',
        textAlign: 'center',
        color: '#605e5c',
        width: '100%',
        height: '100%',
    },
};

export const themeProviderStyles: CSSProperties = {
    height: '100%',
    width: '100%',
};

export const headerStyles: CSSProperties = {
    height: '100px',
    borderBottom: `2px solid ${getColorFromRGBA({r: 0, g: 0, b: 0, a: 0.9})}`,
    padding: '20px',
};
export const headerStackTokens: IStackTokens = {childrenGap: 30};
export const headerInfoStackTokens: IStackTokens = {childrenGap: 2};

export const bodyStyles: CSSProperties = {};
export const bodySectionHeaderStyles: CSSProperties = {
    backgroundColor: 'rgba(128,128,128,0.3)',
    padding: '10px',
    borderBottom: `2px solid rgba(128,128,128,0.3)`,
    fontVariant: 'small-caps',
};
export const bodySectionBodyStyles: CSSProperties = {
    padding: '10px',
};
export const bodySectionWideStyles: CSSProperties = {
    backgroundColor: 'rgba(128,128,128,0.3)',
    minWidth: '500px',
    borderRadius: '10px',
    overflow: 'hidden',
    border: `1px solid rgba(128,128,128,0.3)`,
};
export const bodySectionStyles: CSSProperties = {
    backgroundColor: 'rgba(128,128,128,0.3)',
    minWidth: '300px',
    borderRadius: '10px',
    overflow: 'hidden',
    border: `1px solid rgba(128,128,128,0.3)`,
};
export const bodyStackTokens: IStackTokens = {childrenGap: 15};
export const bodySectionStackTokens: IStackTokens = {childrenGap: 5};
export const bodySectionContentStackTokens: IStackTokens = {childrenGap: 10};

export const footerStyles: CSSProperties = {
    marginBottom: '20px',
};
export const footerStackTokens: IStackTokens = {childrenGap: 10};