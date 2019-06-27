[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

module Input = {
  [@react.component]
  let make = (~value, ~onBlur, ~onClick, ~onChange) =>
    <input
      value
      onClick
      onBlur
      onChange
      type_="text"
      placeholder="select vehicle"
      className="h-8 bg-gray-100 shadow-sm text-sm outline-none w-full px-2 cursor-pointer focus:cursor-text"
    />;
};

module Menu = {
  [@react.component]
  let make = (~children, ~hide) =>
    hide ?
      <div className="absolute shadow-md bg-white w-full z-10">
        children
      </div> :
      React.null;
  module Item = {
    [@react.component]
    let make = (~value, ~onClick) =>
      <div
        className="cursor-pointer vertial-align-middle h-8 text-sm align-content-center leading-loose px-2 hover:bg-gray-200"
        onClick>
        {React.string(value)}
      </div>;
  };
};

module Box = {
  [@react.component]
  let make = (~children) =>
    <div className="inline-block relative bg-white w-full"> children </div>;
};
module Container = {
  [@react.component]
  let make = (~children) => <div className="block w-full"> children </div>;
};

[@react.component]
let make = (~values: list(string), ~onChange) => {
  let (active, toggleActive) = React.useState(_ => false);
  let (value, changeValue) = React.useState(_ => "");

  let handleClick = _e => {
    toggleActive(active => !active);
    changeValue(value => active ? value : "");
  };

  let handleChange = e => ReactEvent.Form.target(e)##value |> changeValue;

  /*
    setTimeout is for avoiding clash btw onBlur and onClick
    onBlur remove Menu from dom on which onClick is register
    thus preventing onClick beign triggered
   */
  let handleBlur = _e => setTimeout(() => toggleActive(_ => false), 200);

  let handleSelect = value => {
    changeValue(_ => value);
    onChange(value);
  };

  <Box>
    <Container>
      <Input
        value
        onBlur=handleBlur
        onClick=handleClick
        onChange=handleChange
      />
      <Menu hide=active>
        {
          values
          |> List.filter(x =>
               Js.String.startsWith(
                 Js.String.toLowerCase(value),
                 Js.String.toLowerCase(x),
               )
             )
          |> List.mapi((i, x) =>
               <Menu.Item
                 key={string_of_int(i)}
                 value=x
                 onClick={_e => handleSelect(x)}
               />
             )
          |> Array.of_list
          |> React.array
        }
      </Menu>
    </Container>
  </Box>;
};