import React, {useEffect, useState} from 'react';
import {DefaultButton, Stack, TextField, ThemeProvider, Toggle} from '@fluentui/react';
import {AzureThemeDark, AzureThemeLight} from '@fluentui/azure-themes';
import './App.css';
import {rootStackStyles, rootStackTokens, themeProviderStyles} from "./styles/GlobalStyles";
import AppHeader from "./components/AppHeader";
import AppBody from "./components/AppBody";
import BodySection from "./components/utilities/BodySection";
import {
  disableBeacon,
  disableFlash,
  disableForcedGreenMode,
  disableForcedOffMode,
  disableForcedRedMode,
  disableForcedYellowMode,
  disablePed,
  enableBeacon,
  enableFlash,
  enableForcedGreenMode,
  enableForcedOffMode,
  enableForcedRedMode,
  enableForcedYellowMode,
  enablePed,
  getState,
  requestWalk
} from "./functions/apiRequests";
import {ApiState} from "./functions/ApiState";
import useLocalStorage from "./utilities/hooks";
import TrafficSignalBulb from "./components/signals/TrafficSignalBulb";
import TrafficSignalBody from "./components/signals/TrafficSignalBody";
import PedestrianSignal from "./components/signals/PedestrianSignal";
import AppFooter from "./components/AppFooter";

export const App: React.FunctionComponent = () => {
  if (process.env.NODE_ENV === 'development') {
    console.log('Running in development mode');
  }

  // Create states
  const [themeName, setThemeName] = useLocalStorage("themeName", AzureThemeDark);
  const [theme, setTheme] = useState(themeName === "light" ? AzureThemeLight : AzureThemeDark);
  const [signalState, setSignalState] = useLocalStorage("signalStateCache", new ApiState());
  const [autoRefresh, setAutoRefresh] = useLocalStorage("autoRefresh", true);

  // Create handler for saving theme
  useEffect(() => {
    setThemeName(theme === AzureThemeLight ? "light" : "dark");
  }, [setThemeName, theme]);

  // Create handler for auto-refreshing state
  useEffect(() => {
    if (autoRefresh) {
      const interval = setInterval(() => {
        getState().then((state) => {
          setSignalState(state);
        });
      }, 500);
      return () => clearInterval(interval);
    }
  }, [autoRefresh, setSignalState]);

  // Update state on load
  useEffect(() => {
    getState().then((state) => {
      setSignalState(state);
    });
  }, [setSignalState]);

  return (
      <ThemeProvider applyTo={"body"} theme={theme} style={themeProviderStyles}>
        <Stack horizontalAlign="center" verticalAlign="space-between" verticalFill styles={rootStackStyles}
               tokens={rootStackTokens}>

          { /* HEADER */}
          <AppHeader/>

          { /* BODY */}
          <AppBody>
            <BodySection title={"Signals"} wide horizontal>
              <PedestrianSignal walk={signalState.lampPrimaryWalk}
                                dontWalk={signalState.lampPrimaryDontWalk}/>
              <TrafficSignalBody>
                <TrafficSignalBulb color={"red"} powered={signalState.lampSecondaryRed}/>
                <TrafficSignalBulb color={"yellow"} powered={signalState.lampSecondaryYellow}/>
                <TrafficSignalBulb color={"green"} powered={signalState.lampSecondaryGreen} thruArrow/>
              </TrafficSignalBody>
              <TrafficSignalBody>
                <TrafficSignalBulb color={"red"} powered={signalState.lampPrimaryRed}/>
                <TrafficSignalBulb color={"yellow"} powered={signalState.lampPrimaryYellow}/>
                <TrafficSignalBulb color={"yellow"} powered={signalState.lampPrimaryYellowArrow}
                                   rightArrow/>
                <TrafficSignalBulb color={"green"} powered={signalState.lampPrimaryGreenArrow} rightArrow/>
              </TrafficSignalBody>
            </BodySection>
            <BodySection title={"Control"}>
              <DefaultButton text="Request Walk" onClick={requestWalk} allowDisabledFocus
                             disabled={signalState.flashMode || signalState.walkRequested || signalState.stateForcedOffMode || signalState.stateForcedRedMode || signalState.stateForcedYellowMode || signalState.stateForcedGreenMode}/>
              <br/>
              <Toggle
                  checked={signalState.pedEnabled}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enablePed().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disablePed().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Pedestrian Signals Enabled"
                  offText="Pedestrian Signal Disabled"/>
              <Toggle
                  checked={signalState.flashMode}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableFlash().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableFlash().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Flash Mode Enabled"
                  offText="Flash Mode Disabled"/>
              <Toggle
                  checked={signalState.stateIsBeaconEnabled}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableBeacon().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableBeacon().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    }
                  }
                  }
                  onText="Beacon Enabled"
                  offText="Beacon Disabled"/>
              <Toggle
                  checked={signalState.stateForcedOffMode}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableForcedOffMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableForcedOffMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Forced Off Mode Enabled"
                  offText="Forced Off Mode Disabled"/>
              <Toggle
                  checked={signalState.stateForcedRedMode}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableForcedRedMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableForcedRedMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Forced Red Mode Enabled"
                  offText="Forced Red Mode Disabled"/>
              <Toggle
                  checked={signalState.stateForcedYellowMode}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableForcedYellowMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableForcedYellowMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Forced Yellow Mode Enabled"
                  offText="Forced Yellow Mode Disabled"/>
              <Toggle
                  checked={signalState.stateForcedGreenMode}
                  onChange={(ev, checked) => {
                    if (checked) {
                      enableForcedGreenMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });
                      });
                    } else {
                      disableForcedGreenMode().then(() => {
                        getState().then((state) => {
                          setSignalState(state);
                        });

                      });
                    }
                  }
                  }
                  onText="Forced Green Mode Enabled"
                  offText="Forced Green Mode Disabled"/>


            </BodySection>
            <BodySection title={"Flash Monitor"}>
              <TrafficSignalBody>
                <TrafficSignalBulb color={"red"} powered={!signalState.statePhaseFlash}/>
                <TrafficSignalBulb color={"red"} powered={signalState.statePhaseFlash}/>
              </TrafficSignalBody>
            </BodySection>
            <BodySection title={"Diagnostic"} wide>
              <Stack.Item>
                <TextField label="Phase Index"
                           value={signalState.statePhaseIndex + " / " + signalState.statePhaseMaxIndex}
                           readOnly={true}/>
              </Stack.Item>
              <Stack.Item>
                <TextField label="Last Phase Time" value={signalState.stateLastTime.toString()}
                           readOnly={true}/>
              </Stack.Item>
            </BodySection>
            <BodySection title={"Settings"}>
              <Toggle
                  checked={autoRefresh}
                  onChange={(ev, checked) => {
                    setAutoRefresh(checked ?? !autoRefresh);
                  }
                  }
                  onText="Auto Refresh"
                  offText="Manual Refresh"/>
              <DefaultButton text="Refresh State" onClick={() => {
                getState().then((state) => {
                  setSignalState(state);
                });
              }} allowDisabledFocus/>
            </BodySection>
          </AppBody>

          { /* FOOTER */}
          <AppFooter theme={theme} setTheme={setTheme}/>
        </Stack>
      </ThemeProvider>
  );
};
