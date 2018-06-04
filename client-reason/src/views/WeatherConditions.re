/* This is the basic component. */
let component = ReasonReact.statelessComponent("WeatherConditions");

/* Handle the "home" action */
let handleClick = (_event, _self) => ReasonReact.Router.push("/");

/* `make` is the function that mandatorily takes `children` (if you want to use
   `JSX). `message` is a named argument, which simulates ReactJS props. Usage:

   `<Page message="hello" />`

   Which desugars to

   `ReasonReact.element(Page.make(~message="hello", [||]))` */
let make = (~currentTemp,
                  ~humidity,
                  ~wind,
                  ~windDirection,
                  ~currentCondition,
                  ~currentConditionDescription,
                  ~weatherIcon,
                  ~cityName, _children) => {
  ...component,
  render: self => <div>
                            <div className='homeBtn'>
                              <button onClick=(_event => self.handle(handleClick))>Home</button>
                            </div>
                            <div className='weatherCardContainer'>
                              <div className='weatherCard'>
                                <img src={weatherIcon} alt='Weather icon'/>
                                <div className='conditionsOverview'>
                                  <p>(ReasonReact.string(currentTemp))</p>
                                  <p>(ReasonReact.string(currentConditionDescription))</p>
                                </div>
                                <div className='conditionDetails'>
                                  <p>(ReasonReact.string(j|Humidity: $(humidity)|j)</p>
                                  <p>(ReasonReact.string(j|Wind Speed: $(wind)|j))</p>
                                </div>
                              </div>

                              <h4>(ReasonReact.string(j|Location | $(cityName)|j))</h4>
                            </div>
                          </div>,
};
